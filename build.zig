const std = @import("std");
const Build = std.Build;
const builtin = @import("builtin");

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
    "hqx/HQ2x.cc",
};

const c_flags_common = [_][]const u8{
    "-std=c++14",
    "-pedantic",
    "-Wall",
    "-Wextra",
    "-Wno-format-truncation",
    "-Wno-missing-field-initializers",
    "-Wno-unused-parameter",
    "-Wno-date-time",
    "-DSDL",
    "-DBOMBERMAAAN_SCALE_2X",
    "-DENABLE_LOG", // Define this if the log file should be enabled
};

const c_flags_dbg = [_][]const u8{
    "-DENABLE_DEBUG_LOG", // Define this if the debug log file should be enabled
};

const c_flags_rel = [_][]const u8{
    "-O2",
    "-DNDEBUG",
};

pub fn build(b: *Build) void {
    var target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});
    const web = target.result.os.tag == .emscripten;
    const emsdk = b.dependency("emsdk", .{});
    b.step("install-emsdk", "Install Emscripten SDK in zig-pkg").dependOn(emSdkInstallStep(b, emsdk));

    if (web) {
        var query = target.query;
        query.cpu_features_add.addFeature(@backingInt(std.Target.wasm.Feature.atomics));
        query.cpu_features_add.addFeature(@backingInt(std.Target.wasm.Feature.bulk_memory));
        target = b.resolveTargetQuery(query);
    }
    var flags: std.ArrayList([]const u8) = .empty;
    flags.appendSlice(b.allocator, &c_flags_common) catch @panic("OOM");
    flags.appendSlice(b.allocator, if (optimize == .debug) &c_flags_dbg else &c_flags_rel) catch @panic("OOM");
    if (web) flags.append(b.allocator, "-fno-sanitize=undefined") catch @panic("OOM");
    const mod = b.createModule(.{
        .target = target,
        .optimize = optimize,
        .link_libc = true,
        .link_libcpp = true,
    });
    mod.addCSourceFiles(.{
        .root = b.path("src"),
        .files = &src_files,
        .flags = flags.items,
    });

    const sysroot_include: ?Build.LazyPath = if (web) emsdk.path("upstream/emscripten/cache/sysroot/include") else null;
    const sdl = b.dependency("sdl", .{
        .target = target,
        .optimize = .fast,
        .emscripten_include = sysroot_include,
    });
    const compat = b.dependency("sdl_compat", .{
        .target = target,
        .optimize = optimize,
        .emscripten_include = sysroot_include,
    });
    const mixer = b.dependency("sdl_mixer", .{
        .target = target,
        .optimize = optimize,
        .emscripten_include = sysroot_include,
    });
    const tinyxml = b.dependency("tinyxml", .{ .target = target, .optimize = optimize });
    const assets = b.dependency("assets", .{ .target = target, .optimize = .fast });
    mod.addIncludePath(compat.artifact("sdl12_compat_static").getEmittedIncludeTree());
    mod.addIncludePath(mixer.artifact("SDL2_mixer").getEmittedIncludeTree());
    mod.addIncludePath(sdl.artifact("SDL2").getEmittedIncludeTree());
    mod.addIncludePath(tinyxml.artifact("tinyxml").getEmittedIncludeTree());
    mod.addIncludePath(b.dependency("simpleini", .{}).path(""));
    mod.addIncludePath(b.dependency("pstl", .{}).path("include"));
    mod.addIncludePath(assets.artifact("bombermaaan_assets").getEmittedIncludeTree());
    mod.linkLibrary(tinyxml.artifact("tinyxml"));
    mod.linkLibrary(compat.artifact("sdl12_compat_static"));
    mod.linkLibrary(mixer.artifact("SDL2_mixer"));
    mod.linkLibrary(assets.artifact("bombermaaan_assets"));

    if (web) {
        const lib = b.addLibrary(.{ .name = "bombermaaan", .root_module = mod });
        for (lib.getCompileDependencies(false)) |dependency| {
            for (dependency.root_module.getGraph().modules) |module| {
                module.addSystemIncludePath(sysroot_include.?);
            }
        }
        const install = emLinkStep(b, emsdk, lib, optimize);
        b.getInstallStep().dependOn(&install.step);
        b.installFile("web_assets/coi-serviceworker.js", "web/coi-serviceworker.js");
        const run = b.addRunFile(emTool(b, emsdk, "emrun"));
        run.addFileArg(.{ .relative = .{ .base = .install_prefix, .sub_path = "web/index.html" } });
        run.step.dependOn(b.getInstallStep());
        b.step("run", "Run Bombermaaan in a browser via emrun").dependOn(&run.step);
    } else {
        const exe = b.addExecutable(.{ .name = "bombermaaan", .root_module = mod });
        b.installArtifact(exe);
        const run = b.addRunArtifact(exe);
        b.step("run", "Run Bombermaaan on the desktop").dependOn(&run.step);
    }
}

// Emscripten links the C++ game, its libraries, and embedded assets.
fn emLinkStep(b: *Build, emsdk: *Build.Dependency, lib: *Build.Step.Compile, optimize: std.builtin.Optimize) *Build.Step.InstallDir {
    const empp = b.addRunFile(emTool(b, emsdk, "em++"));
    empp.setName("em++");
    if (optimize == .debug) {
        empp.addArgs(&.{ "-g", "-Og", "-sSAFE_HEAP=1", "-sSTACK_OVERFLOW_CHECK=1" });
        empp.addArg("-gsource-map");
        empp.addArg("--emrun");
    } else {
        empp.addArg("-sASSERTIONS=0");
        empp.addArg(if (optimize == .small) "-Oz" else "-O3");
        empp.addArgs(&.{ "-flto", "--closure", "1" });
    }
    empp.addArgs(&.{
        "-sMALLOC=emmalloc",
        "-pthread",
        "-sPTHREAD_POOL_SIZE=navigator.hardwareConcurrency",
        // Zig's Debug runtime references filesystem and socket support.
        "-sFILESYSTEM=1",
        "-sGL_ENABLE_GET_PROC_ADDRESS=1",
        "-sINITIAL_MEMORY=64MB",
        "-sSTACK_SIZE=16MB",
        "-sFULL_ES3=1",
        "-sASYNCIFY=1",
    });
    empp.addPrefixedFileArg("--shell-file=", b.path("web_assets/shell_minimal.html"));
    empp.addArtifactArg(lib);
    for (lib.getCompileDependencies(false)) |dependency| {
        if (dependency != lib and dependency.kind == .lib) empp.addArtifactArg(dependency);
    }
    empp.addArg("-o");
    const output = empp.addOutputFileArg("index.html");
    return b.addInstallDirectory(.{
        .source_dir = output.dirname(),
        .install_dir = .prefix,
        .install_subdir = "web",
    });
}

fn emTool(b: *Build, emsdk: *Build.Dependency, tool: []const u8) Build.LazyPath {
    const filename = if (builtin.os.tag == .windows) b.fmt("{s}.exe", .{tool}) else tool;
    return emsdk.path(b.pathJoin(&.{ "upstream", "emscripten", filename }));
}

fn createEmsdkStep(b: *Build, emsdk: *Build.Dependency) *Build.Step.Run {
    if (builtin.os.tag == .windows) {
        return b.addRunFile(emsdk.path("emsdk.bat"));
    } else {
        const run = b.addSystemCommand(&.{"bash"});
        run.addFileArg(emsdk.path("emsdk"));
        return run;
    }
}

fn emSdkInstallStep(b: *Build, emsdk: *Build.Dependency) *Build.Step {
    const install = createEmsdkStep(b, emsdk);
    install.addArgs(&.{ "install", "7.0.0" });
    const activate = createEmsdkStep(b, emsdk);
    activate.addArgs(&.{ "activate", "7.0.0" });
    activate.step.dependOn(&install.step);
    return &activate.step;
}
