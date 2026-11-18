const std = @import("std");
const Build = std.Build;

const src_files = [_][]const u8{
    "tinystr.cpp",
    "tinyxml.cpp",
    "tinyxmlerror.cpp",
    "tinyxmlparser.cpp",
};

pub fn build(b: *Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const use_stl = b.option(bool, "use_stl", "Use C++ standard template library types") orelse false;
    const c_flags: []const []const u8 = if (target.result.os.tag == .emscripten)
        (if (use_stl) &.{ "-fno-sanitize=undefined", "-DTIXML_USE_STL" } else &.{"-fno-sanitize=undefined"})
    else if (use_stl) &.{"-DTIXML_USE_STL"} else &.{};

    const lib = b.addLibrary(.{
        .name = "tinyxml",
        .root_module = b.createModule(.{
            .target = target,
            .optimize = optimize,
        }),
    });
    lib.root_module.addCSourceFiles(.{ .root = b.path("src/"), .files = &src_files, .flags = c_flags });

    lib.root_module.link_libc = true;
    lib.root_module.link_libcpp = true;

    lib.installHeader(b.path("src/tinyxml.h"), "tinyxml.h");
    lib.installHeader(b.path("src/tinystr.h"), "tinystr.h");
    b.installArtifact(lib);
}
