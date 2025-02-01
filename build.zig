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
    "hqx/HQx.cc",
    "hqx/HQ2x.cc",
};

const c_flags_common = [_][]const u8{
    "-std=c++14",
    "-pedantic",
    "-Wall",
    "-Wextra",
    "-Wno-format-truncation",
    "-Wno-missing-field-initializers",
    "-Wno-date-time",
    "-DSDL",
    "-DENABLE_LOG", // Define this if the log file should be enabled
};

const c_flags_dbg = [_][]const u8{
    "-DENABLE_DEBUG_LOG", // Define this if the debug log file should be enabled
};

const c_flags_rel = [_][]const u8{
    "-O2",
    "-DNDEBUG",
};

pub fn build(b: *Build) !void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});
    const c_flags: []const []const u8 = if (optimize == .Debug)
        &(c_flags_common ++ c_flags_dbg)
    else
        &(c_flags_common ++ c_flags_rel);

    // Setup sysroot with Emscripten so dependencies know where the system include files are
    const resolved_target = if (target.result.os.tag == .emscripten) blk: {
        const emsdk_sysroot = b.pathJoin(&.{ emSdkPath(b), "upstream", "emscripten", "cache", "sysroot" });
        b.sysroot = emsdk_sysroot;

        var target_query = target.query;
        for (target.result.cpu.arch.allFeaturesList(), 0..) |feature, index_usize| {
            const index = @as(std.Target.Cpu.Feature.Set.Index, @intCast(index_usize));
            if (feature.llvm_name) |llvm_name| {
                if (std.mem.eql(u8, llvm_name, "atomics") or std.mem.eql(u8, llvm_name, "bulk-memory")) {
                    target_query.cpu_features_add.addFeature(index);
                }
            }
        }

        const new_target = b.resolveTargetQuery(std.Target.Query{
            .cpu_arch = target_query.cpu_arch,
            .cpu_model = target_query.cpu_model,
            .cpu_features_add = target_query.cpu_features_add,
            .cpu_features_sub = target_query.cpu_features_sub,
            .os_tag = .emscripten,
            .os_version_min = target_query.os_version_min,
            .os_version_max = target_query.os_version_max,
            .glibc_version = target_query.glibc_version,
            .abi = target_query.abi,
            .dynamic_linker = target_query.dynamic_linker,
            .ofmt = target_query.ofmt,
        });

        break :blk new_target;
    } else blk: {
        break :blk target;
    };

    std.log.info("resolved target: arch {s}, cpu_model {s}, os {s}", .{
        resolved_target.result.cpu.arch.genericName(),
        resolved_target.result.cpu.model.name,
        @tagName(resolved_target.result.os.tag),
    });
    for (resolved_target.result.cpu.arch.allFeaturesList(), 0..) |feature, index_usize| {
        const index = @as(std.Target.Cpu.Feature.Set.Index, @intCast(index_usize));
        const is_enabled = resolved_target.result.cpu.features.isEnabled(index);
        if (feature.llvm_name) |llvm_name| {
            std.log.info("    feature {s} {s}", .{ llvm_name, if (is_enabled) "enabled" else "disabled" });
        } else {
            std.log.info("    feature (unnamed) {s}", .{if (is_enabled) "enabled" else "disabled"});
        }
    }

    const sdl_dep = b.dependency("sdl", .{
        .target = resolved_target,
        .optimize = optimize,
    });
    const sdl_compat_dep = b.dependency("sdl_compat", .{
        .target = resolved_target,
        .optimize = optimize,
    });
    const sdl_mixer_dep = b.dependency("sdl_mixer", .{
        .target = resolved_target,
        .optimize = optimize,
    });
    const tinyxml_dep = b.dependency("tinyxml", .{
        .target = resolved_target,
        .optimize = optimize,
    });
    const simpleini_dep = b.dependency("simpleini", .{
        .target = resolved_target,
        .optimize = optimize,
    });
    const pstl_dep = b.dependency("pstl", .{ .target = resolved_target, .optimize = optimize });
    const assets_dep = b.dependency("assets", .{
        .target = resolved_target,
        .optimize = optimize,
    });

    const exe = if (resolved_target.result.os.tag == .emscripten) try compileEmscripten(
        b,
        "bombermaaan",
        resolved_target,
        optimize,
    ) else b.addExecutable(.{
        .name = "bombermaaan",
        .target = resolved_target,
        .optimize = optimize,
    });
    exe.addCSourceFiles(.{ .root = b.path("src/"), .files = &src_files, .flags = c_flags });
    exe.root_module.addIncludePath(sdl_compat_dep.artifact("sdl12_compat_static").getEmittedIncludeTree());
    exe.root_module.addIncludePath(sdl_mixer_dep.artifact("SDL2_mixer").getEmittedIncludeTree());
    exe.root_module.addIncludePath(sdl_dep.artifact("SDL2").getEmittedIncludeTree());
    exe.root_module.addIncludePath(tinyxml_dep.artifact("tinyxml").getEmittedIncludeTree());
    exe.root_module.addIncludePath(simpleini_dep.path(""));
    exe.root_module.addIncludePath(pstl_dep.path("include"));
    exe.root_module.addIncludePath(assets_dep.artifact("bombermaaan_assets").getEmittedIncludeTree());

    exe.linkLibC();
    exe.linkLibrary(tinyxml_dep.artifact("tinyxml"));
    exe.linkLibrary(sdl_compat_dep.artifact("sdl12_compat_static"));
    exe.linkLibrary(sdl_mixer_dep.artifact("SDL2_mixer"));
    exe.linkLibrary(assets_dep.artifact("bombermaaan_assets"));

    if (resolved_target.result.os.tag == .emscripten) {
        const link_step = try emLinkAndInstallStep(b, .{
            .target = resolved_target,
            .optimize = optimize,
            .lib_main = exe,
        });

        // ...and a special run step to run the build result via emrun
        var run = emRunStep(b, .{ .web_path = b.getInstallPath(.prefix, "web") });
        run.step.dependOn(&link_step.step);

        const run_cmd = b.step("run", "Run the demo for web via emrun");
        run_cmd.dependOn(&run.step);
    } else {
        b.installArtifact(exe);

        const run_cmd = b.addRunArtifact(exe);
        run_cmd.step.dependOn(b.getInstallStep());

        const run = b.step("run", "Run the demo for desktop");
        run.dependOn(&run_cmd.step);
    }
}

// Creates the static library to build a project for Emscripten.
pub fn compileEmscripten(
    b: *std.Build,
    name: []const u8,
    resolved_target: std.Build.ResolvedTarget,
    optimize: std.builtin.Mode,
) !*std.Build.Step.Compile {
    // The project is built as a library and linked later.
    const exe_lib = b.addStaticLibrary(.{
        .name = name,
        .target = resolved_target,
        .optimize = optimize,
    });

    exe_lib.addSystemIncludePath(.{ .cwd_relative = b.pathJoin(&.{
        emSdkPath(b),
        "upstream",
        "emscripten",
        "cache",
        "sysroot",
        "include",
    }) });

    return exe_lib;
}

// One-time setup of the Emscripten SDK (runs 'emsdk install + activate'). If the
// SDK had to be setup, a run step will be returned which should be added
// as dependency to the sokol library (since this needs the emsdk in place),
// if the emsdk was already setup, null will be returned.
// NOTE: ideally this would go into a separate emsdk-zig package
fn emSdkSetupStep(b: *std.Build) !?*std.Build.Step.Run {
    const emsdk_path = emSdkPath(b);
    const dot_emsc_path = b.pathJoin(&.{ emsdk_path, ".emscripten" });
    const dot_emsc_exists = !std.meta.isError(std.fs.accessAbsolute(dot_emsc_path, .{}));
    if (!dot_emsc_exists) {
        var cmd = std.ArrayList([]const u8).init(b.allocator);
        defer cmd.deinit();
        if (builtin.os.tag == .windows)
            try cmd.append(b.pathJoin(&.{ emsdk_path, "emsdk.bat" }))
        else {
            try cmd.append("bash"); // or try chmod
            try cmd.append(b.pathJoin(&.{ emsdk_path, "emsdk" }));
        }
        const emsdk_install = b.addSystemCommand(cmd.items);
        emsdk_install.addArgs(&.{ "install", "latest" });
        const emsdk_activate = b.addSystemCommand(cmd.items);
        emsdk_activate.addArgs(&.{ "activate", "latest" });
        emsdk_activate.step.dependOn(&emsdk_install.step);
        return emsdk_activate;
    } else {
        return null;
    }
}

// for wasm32-emscripten, need to run the Emscripten linker from the Emscripten SDK
pub const EmLinkOptions = struct {
    target: Build.ResolvedTarget,
    optimize: std.builtin.OptimizeMode,
    lib_main: *Build.Step.Compile, // the actual Zig code must be compiled to a static link library
    release_use_closure: bool = true,
    release_use_lto: bool = true,
    use_emmalloc: bool = true,
    use_pthreads: bool = true,
    use_webgl2: bool = false,
    use_webgpu: bool = false,
    use_filesystem: bool = true,
    use_asyncify: bool = true,
    shell_file_path: ?[]const u8 = null,
};

fn emLinkAndInstallStep(b: *Build, options: EmLinkOptions) !*Build.Step.Run {
    const emcc_path = b.pathJoin(&.{ emSdkPath(b), "upstream", "emscripten", "em++" });

    // create a separate output directory zig-out/web
    try std.fs.cwd().makePath(b.fmt("{s}/web", .{b.install_path}));

    var emcc_cmd = std.ArrayList([]const u8).init(b.allocator);
    defer emcc_cmd.deinit();

    try emcc_cmd.append(emcc_path);
    if (options.optimize == .Debug) {
        try emcc_cmd.append("-Og");
        try emcc_cmd.append("-sASSERTIONS=1");
        try emcc_cmd.append("-sSAFE_HEAP=1");
        try emcc_cmd.append("-sSTACK_OVERFLOW_CHECK=1");
        try emcc_cmd.append("-gsource-map"); // NOTE(jae): debug sourcemaps in browser, so you can see the stack of crashes
        try emcc_cmd.append("--emrun"); // NOTE(jae): This flag injects code into the generated Module object to enable capture of stdout, stderr and exit(), ie. outputs it in the terminal
    } else {
        try emcc_cmd.append("-sASSERTIONS=0");
        if (options.optimize == .ReleaseSmall) {
            try emcc_cmd.append("-Oz");
        } else {
            try emcc_cmd.append("-O3");
        }
        if (options.release_use_lto) {
            try emcc_cmd.append("-flto");
            try emcc_cmd.append("-Wl,-u,_emscripten_run_callback_on_thread");
        }
        if (options.release_use_closure) {
            try emcc_cmd.append("--closure");
            try emcc_cmd.append("1");
        }
    }
    if (options.use_emmalloc) {
        try emcc_cmd.append("-sMALLOC='emmalloc'");
    }
    if (options.use_pthreads) {
        try emcc_cmd.append("-pthread");
        try emcc_cmd.append("-sUSE_PTHREADS=1");
        try emcc_cmd.append("-sPTHREAD_POOL_SIZE=navigator.hardwareConcurrency");
    }
    if (options.use_webgl2) {
        try emcc_cmd.append("-sUSE_WEBGL2=1");
    }
    if (options.use_webgpu) {
        try emcc_cmd.append("-sUSE_WEBGPU=1");
    }
    if (!options.use_filesystem) {
        try emcc_cmd.append("-sFILESYSTEM=0");
        try emcc_cmd.append("-sNO_FILESYSTEM=1");
    }
    if (options.shell_file_path) |shell_file_path| {
        try emcc_cmd.append(b.fmt("--shell-file={s}", .{shell_file_path}));
    }
    // NOTE(jae): 0224-02-22
    // Need to fix this linker issue
    // linker: Undefined symbol: eglGetProcAddress(). Please pass -sGL_ENABLE_GET_PROC_ADDRESS at link time to link in eglGetProcAddress().
    try emcc_cmd.append("-sGL_ENABLE_GET_PROC_ADDRESS=1");
    try emcc_cmd.append("-sINITIAL_MEMORY=64Mb");
    try emcc_cmd.append("-sSTACK_SIZE=16Mb");

    // NOTE(jae): 2024-02-24
    // Needed or zig crashes with "Aborted(Cannot use convertFrameToPC (needed by __builtin_return_address) without -sUSE_OFFSET_CONVERTER)"
    // for os_tag == .emscripten.
    // However currently then it crashes when trying to call "std.debug.captureStackTrace"
    try emcc_cmd.append("-sUSE_OFFSET_CONVERTER=1");
    try emcc_cmd.append("-sFULL_ES3=1");
    try emcc_cmd.append("-sUSE_GLFW=3");
    if (options.use_asyncify) {
        try emcc_cmd.append("-sASYNCIFY");
    }

    try emcc_cmd.append(b.fmt("-o{s}/{s}.html", .{ b.getInstallPath(.prefix, "web"), options.lib_main.name }));
    try emcc_cmd.append("--shell-file");
    try emcc_cmd.append("web_assets/shell_minimal.html");

    const emcc = b.addSystemCommand(emcc_cmd.items);
    emcc.setName("emcc"); // hide emcc path

    // one-time setup of Emscripten SDK
    const maybe_emsdk_setup = try emSdkSetupStep(b);
    if (maybe_emsdk_setup) |emsdk_setup| {
        options.lib_main.step.dependOn(&emsdk_setup.step);
    }

    // get sysroot include
    const sysroot_include_path = if (b.sysroot) |sysroot|
        b.pathJoin(&.{ sysroot, "include" })
    else
        @panic("unable to get sysroot path");

    // add the main lib, and then scan for library dependencies and add those too
    emcc.addArtifactArg(options.lib_main);
    var it = options.lib_main.root_module.iterateDependencies(options.lib_main, false);
    while (it.next()) |item| {
        if (maybe_emsdk_setup) |emsdk_setup| {
            item.compile.?.step.dependOn(&emsdk_setup.step);
        }
        if (sysroot_include_path.len > 0) {
            // add emscripten system includes to each module, this ensures that any C-modules you import
            // will "just work", assuming it'll run under Emscripten
            item.module.addSystemIncludePath(.{ .cwd_relative = sysroot_include_path });
        }
        for (item.module.link_objects.items) |link_object| {
            switch (link_object) {
                .other_step => |compile_step| {
                    switch (compile_step.kind) {
                        .lib => {
                            emcc.addArtifactArg(compile_step);
                        },
                        else => {},
                    }
                },
                else => {},
            }
        }
    }

    const install_coi = b.addInstallFile(b.path("web_assets/coi-serviceworker.js"), "web/coi-serviceworker.js");

    const install_index = b.addSystemCommand(&.{
        "mv",
        b.fmt("{s}/{s}.html", .{ b.getInstallPath(.prefix, "web"), options.lib_main.name }),
        b.fmt("{s}/index.html", .{b.getInstallPath(.prefix, "web")}),
    });

    install_index.step.dependOn(&emcc.step);
    install_index.step.dependOn(&install_coi.step);
    b.getInstallStep().dependOn(&install_index.step);

    return install_index;
}

// build a run step which uses the emsdk emrun command to run a build target in the browser
pub const EmRunOptions = struct {
    web_path: []const u8,
};

fn emRunStep(b: *std.Build, options: EmRunOptions) *std.Build.Step.Run {
    const emrun_path = b.pathJoin(&.{ emSdkPath(b), "upstream", "emscripten", "emrun" });
    // NOTE(jae): 2024-02-24
    // Default browser to chrome as it has the better WASM debugging tools / UX
    const emrun = b.addSystemCommand(&.{
        emrun_path,
        "--serve_after_exit",
        "--serve_after_close",
        "--browser=chrome",
        options.web_path,
    });
    return emrun;
}

fn emSdkPath(b: *std.Build) []const u8 {
    const emsdk = b.dependency("emsdk", .{});
    const emsdk_path = emsdk.path("").getPath(b);
    return emsdk_path;
}
