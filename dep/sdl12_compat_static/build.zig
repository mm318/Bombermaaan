const std = @import("std");
const builtin = @import("builtin");

const src_files = [_][]const u8{
    "SDL12_compat.c",
};

pub fn build(b: *std.Build) !void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const sdl_dep = b.dependency("sdl", .{
        .target = target,
        .optimize = .ReleaseFast,
    });

    const lib = b.addStaticLibrary(.{
        .name = "sdl12-compat",
        .target = target,
        .optimize = optimize,
    });
    lib.addCSourceFiles(.{ .root = b.path("src/"), .files = &src_files });
    lib.addIncludePath(sdl_dep.artifact("SDL2").getEmittedIncludeTree());

    lib.linkLibC();
    lib.linkLibrary(sdl_dep.artifact("SDL2"));

    b.installArtifact(lib);
}
