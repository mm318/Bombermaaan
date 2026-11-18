const std = @import("std");

const src_files = [_][]const u8{
    "SDL12_compat.c",
};

pub fn build(b: *std.Build) !void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const emscripten_include = b.option(std.Build.LazyPath, "emscripten_include", "Emscripten sysroot include directory");
    const sdl_dep = b.dependency("sdl", .{
        .target = target,
        .optimize = .fast,
        .emscripten_include = emscripten_include,
    });

    const lib = b.addLibrary(.{
        .name = "sdl12_compat_static",
        .root_module = b.createModule(.{
            .target = target,
            .optimize = optimize,
        }),
    });
    lib.root_module.addCSourceFiles(.{
        .root = b.path("src"),
        .files = &src_files,
        .flags = if (target.result.os.tag == .emscripten) &.{"-fno-sanitize=undefined"} else &.{},
    });
    lib.root_module.addIncludePath(sdl_dep.artifact("SDL2").getEmittedIncludeTree());

    lib.root_module.link_libc = true;
    lib.root_module.linkLibrary(sdl_dep.artifact("SDL2"));

    lib.installHeadersDirectory(b.path("include"), "", .{});
    b.installArtifact(lib);
}
