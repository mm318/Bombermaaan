const std = @import("std");
const Build = std.Build;

const src_files = [_][]const u8{
    "tinystr.cpp",
    "tinyxml.cpp",
    "tinyxmlerror.cpp",
    "tinyxmlparser.cpp",
};

const c_flags: []const []const u8 = &.{
    "-DTIXML_USE_STL",
};

pub fn build(b: *Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const lib = b.addStaticLibrary(.{
        .name = "tinyxml",
        .target = target,
        .optimize = optimize,
    });
    lib.addCSourceFiles(.{ .root = b.path("src/"), .files = &src_files, .flags = c_flags });

    lib.linkLibC();
    lib.linkLibCpp();

    b.installArtifact(lib);
}
