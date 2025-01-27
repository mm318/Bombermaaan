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
    "StdAfx.cpp",
    "WinMain.cpp",
    "WinReplace.cpp",
    // "Bombermaaan.rc",
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
    "-DLOAD_RESOURCES_FROM_FILES",
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

    exe.linkLibCpp();
    exe.linkLibrary(tinyxml_dep.artifact("tinyxml"));
    exe.linkLibrary(sdl_compat_dep.artifact("sdl12_compat_static"));
    exe.linkLibrary(sdl_mixer_dep.artifact("SDL2_mixer"));

    b.installArtifact(exe);

    const run_cmd = b.addRunArtifact(exe);
    const assets_cmd = ExtractAssetsStep.create(b, b.path("assets/game_assets.zip"), .bin, "");
    run_cmd.step.dependOn(&assets_cmd.step);
    run_cmd.step.dependOn(b.getInstallStep());

    const run = b.step("run", "Run the game on desktop");
    run.dependOn(&run_cmd.step);
}

const ExtractAssetsStep = struct {
    step: std.Build.Step,
    source: std.Build.LazyPath,
    dest_type: std.Build.InstallDir,
    dest_subpath: []const u8,

    pub fn create(
        owner: *std.Build,
        source: std.Build.LazyPath,
        dest_type: std.Build.InstallDir,
        dest_subpath: []const u8,
    ) *ExtractAssetsStep {
        const extract_step = owner.allocator.create(ExtractAssetsStep) catch @panic("OOM");
        extract_step.* = .{
            .step = std.Build.Step.init(.{
                .id = .custom,
                .name = owner.fmt("extract {s} assets to {s}", .{ @tagName(dest_type), dest_subpath }),
                .owner = owner,
                .makeFn = make,
            }),
            .source = source.dupe(owner),
            .dest_type = dest_type.dupe(owner),
            .dest_subpath = owner.dupePath(dest_subpath),
        };
        return extract_step;
    }

    fn make(step: *std.Build.Step, _: std.Build.Step.MakeOptions) !void {
        const b = step.owner;
        const extract_step: *ExtractAssetsStep = @fieldParentPtr("step", step);
        try step.singleUnchangingWatchInput(extract_step.source);

        const full_src_path = extract_step.source.getPath2(b, step);
        const full_dest_path = b.getInstallPath(extract_step.dest_type, extract_step.dest_subpath);

        const dest_dir = try std.fs.openDirAbsolute(full_dest_path, .{});
        const src_file = try std.fs.openFileAbsolute(full_src_path, .{});
        const src_stream = std.fs.File.seekableStream(src_file);
        std.zip.extract(dest_dir, src_stream, .{}) catch |err| switch (err) {
            error.PathAlreadyExists => {},
            else => |e| return e,
        };

        step.result_cached = true;
    }
};
