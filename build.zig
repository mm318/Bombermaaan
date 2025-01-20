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
    "CVideo.cpp",
    "CVideoSDL.cpp",
    "CWall.cpp",
    "CWindow.cpp",
    "CWinner.cpp",
    "StdAfx.cpp",
    "WinMain.cpp",
    "WinReplace.cpp",
    // "Bombermaaan.rc",
};

const c_flags: []const []const u8 = &.{
    "-std=c++11",
    "-pedantic",
    "-Wall",
    "-Wextra",
    "-Wno-format-truncation",
    "-Wno-missing-field-initializers",
    "-O2",
    "-DNDEBUG",
    "-DTIXML_USE_STL",
    "-DSDL",
    "-DLOAD_RESOURCES_FROM_FILES",
};

pub fn build(b: *Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const sdl_dep = b.dependency("sdl", .{
        .target = target,
        .optimize = .ReleaseFast,
    });
    const sdl_compat_dep = b.dependency("sdl_compat", .{
        .target = target,
        .optimize = .ReleaseFast,
    });
    const sdl_mixer_dep = b.dependency("sdl_mixer", .{
        .target = target,
        .optimize = .ReleaseFast,
    });
    const tinyxml_dep = b.dependency("tinyxml", .{
        .target = target,
        .optimize = .ReleaseFast,
    });
    const simpleini_dep = b.dependency("simpleini", .{
        .target = target,
        .optimize = .ReleaseFast,
    });

    const exe = b.addExecutable(.{
        .name = "bombermaaan",
        .target = target,
        .optimize = optimize,
    });
    exe.addCSourceFiles(.{ .root = b.path("src/"), .files = &src_files, .flags = c_flags });
    // exe.root_module.addIncludePath(sdl_dep.path("include/"));
    exe.root_module.addIncludePath(sdl_compat_dep.path("include/"));
    exe.root_module.addIncludePath(sdl_mixer_dep.path("include/"));
    exe.root_module.addIncludePath(tinyxml_dep.path("src/"));
    exe.root_module.addIncludePath(simpleini_dep.path(""));

    exe.linkLibCpp();
    exe.linkLibrary(tinyxml_dep.artifact("tinyxml"));
    exe.linkLibrary(sdl_compat_dep.artifact("sdl12-compat"));
    exe.linkLibrary(sdl_mixer_dep.artifact("SDL2_mixer"));
    if (target.query.isNativeOs() and target.result.os.tag == .linux) {
        exe.linkSystemLibrary("SDL2"); // The SDL package doesn't work for Linux yet, so we rely on system packages for now.
    } else {
        exe.linkLibrary(sdl_dep.artifact("SDL2"));
    }

    b.installArtifact(exe);
}
