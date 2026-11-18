const std = @import("std");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});
    const extractor = b.addExecutable(.{
        .name = "extract-assets",
        .root_module = b.createModule(.{
            .root_source_file = b.path("extract.zig"),
            .target = b.graph.host,
            .optimize = .safe,
        }),
    });
    const extract = b.addRunArtifact(extractor);
    extract.addFileArg(b.path("game_assets.zip"));
    const extracted = extract.addOutputDirectoryArg("assets");
    const files = b.addWriteFiles();
    _ = files.addCopyDirectory(extracted, ".", .{});
    const source = files.addCopyFile(b.path("BombermaaanAssets.zig"), "BombermaaanAssets.zig");
    const lib = b.addLibrary(.{
        .name = "bombermaaan_assets",
        .root_module = b.createModule(.{
            .root_source_file = source,
            .target = target,
            .optimize = optimize,
        }),
    });
    lib.installHeader(b.path("BombermaaanAssets.h"), "BombermaaanAssets.h");
    b.installArtifact(lib);
}
