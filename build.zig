const std = @import("std");
const Build = std.Build;

const src_files = [_][]const u8{
    "CAiArena.cpp",
    "CAiBomber.cpp",
    "CAiManager.cpp",
    "CArena.cpp",
    "CArenaCloser.cpp",
    "CArenaSnapshot.cpp",
    "CBoard.cpp",
    "CBomb.cpp",
    "CBomber.cpp",
    "CBomberMove.cpp",
    "CClock.cpp",
    "CCloudManager.cpp",
    "CCommandChunk.cpp",
    "CConsole.cpp",
    "CControls.cpp",
    "CCredits.cpp",
    "CDebug.cpp",
    "CDemo.cpp",
    "CDisplay.cpp",
    "CDrawGame.cpp",
    "CElement.cpp",
    "CExplosion.cpp",
    "CFloor.cpp",
    "CFont.cpp",
    "CGame.cpp",
    "CHelp.cpp",
    "CHurryMessage.cpp",
    "CInput.cpp",
    "CInputSDL.cpp",
    "CItem.cpp",
    "CLevel.cpp",
    "CLog.cpp",
    "CMainInput.cpp",
    "CMatch.cpp",
    "CMenu.cpp",
    "CMenuBase.cpp",
    "CMenuBomber.cpp",
    "CMenuInput.cpp",
    "CMenuLevel.cpp",
    "CMenuMatch.cpp",
    "CMenuTeam.cpp",
    "CMenuYesNo.cpp",
    "CModeScreen.cpp",
    "CMosaic.cpp",
    "COptions.cpp",
    "CPauseMessage.cpp",
    "CPlayerInput.cpp",
    "CRandomMosaic.cpp",
    "CScores.cpp",
    "CScroller.cpp",
    "CSound.cpp",
    "CTitle.cpp",
    "CTeam.cpp",
    "CVictory.cpp",
    "CVideoSDL.cpp",
    "CWall.cpp",
    "CWindow.cpp",
    "CWinner.cpp",
    "WinMain.cpp",
    "WinReplace.cpp",
};

const c_flags_common = [_][]const u8{
    "-std=c++11",
    "-pedantic",
    "-Wall",
    "-Wextra",
    "-Wno-format-truncation",
    "-Wno-missing-field-initializers",
    "-Wno-date-time",
    "-DTIXML_USE_STL",
    "-DSDL",
};

const c_flags_dbg = [_][]const u8{
    "-DENABLE_LOG",
    "-DENABLE_DEBUG_LOG",
};

const c_flags_rel = [_][]const u8{
    "-O2",
    "-DNDEBUG",
};

pub fn build(b: *Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const c_flags = c_flags_common ++ if (optimize == .Debug) c_flags_dbg else c_flags_rel;

    const sdl_dep = b.dependency("sdl", .{
        .target = target,
        .optimize = optimize,
    });
    const sdl_compat_dep = b.dependency("sdl_compat", .{
        .target = target,
        .optimize = optimize,
    });
    const sdl_mixer_dep = b.dependency("sdl_mixer", .{
        .target = target,
        .optimize = optimize,
    });
    const tinyxml_dep = b.dependency("tinyxml", .{
        .target = target,
        .optimize = optimize,
        .use_stl = true,
    });
    const simpleini_dep = b.dependency("simpleini", .{
        .target = target,
        .optimize = optimize,
    });
    const assets_dep = b.dependency("assets", .{
        .target = target,
        .optimize = optimize,
    });

    const exe = b.addExecutable(.{
        .name = "bombermaaan",
        .target = target,
        .optimize = optimize,
    });
    exe.addCSourceFiles(.{ .root = b.path("src/"), .files = &src_files, .flags = &c_flags });
    exe.root_module.addIncludePath(sdl_compat_dep.artifact("sdl12_compat_static").getEmittedIncludeTree());
    exe.root_module.addIncludePath(sdl_mixer_dep.artifact("SDL2_mixer").getEmittedIncludeTree());
    exe.root_module.addIncludePath(sdl_dep.artifact("SDL2").getEmittedIncludeTree());
    exe.root_module.addIncludePath(tinyxml_dep.artifact("tinyxml").getEmittedIncludeTree());
    exe.root_module.addIncludePath(simpleini_dep.path(""));
    exe.root_module.addIncludePath(assets_dep.artifact("bombermaaan_assets").getEmittedIncludeTree());

    exe.linkLibCpp();
    exe.linkLibrary(tinyxml_dep.artifact("tinyxml"));
    exe.linkLibrary(sdl_compat_dep.artifact("sdl12_compat_static"));
    exe.linkLibrary(sdl_mixer_dep.artifact("SDL2_mixer"));
    exe.linkLibrary(assets_dep.artifact("bombermaaan_assets"));

    b.installArtifact(exe);

    const run_cmd = b.addRunArtifact(exe);
    run_cmd.step.dependOn(b.getInstallStep());

    const run = b.step("run", "Run the game on desktop");
    run.dependOn(&run_cmd.step);
}
