const std = @import("std");
const builtin = @import("builtin");

const src_files = [_][]const u8{
    "codecs/load_aiff.c",
    "codecs/load_voc.c",
    "codecs/mp3utils.c",
    "codecs/music_cmd.c",
    "codecs/music_drflac.c",
    "codecs/music_flac.c",
    "codecs/music_fluidsynth.c",
    "codecs/music_gme.c",
    "codecs/music_minimp3.c",
    "codecs/music_modplug.c",
    "codecs/music_mpg123.c",
    "codecs/music_nativemidi.c",
    "codecs/music_ogg.c",
    "codecs/music_ogg_stb.c",
    "codecs/music_opus.c",
    "codecs/music_timidity.c",
    "codecs/music_wav.c",
    "codecs/music_wavpack.c",
    "codecs/music_xmp.c",
    "effect_position.c",
    "effect_stereoreverse.c",
    "effects_internal.c",
    "mixer.c",
    "music.c",
    "utils.c",
};

pub fn build(b: *std.Build) !void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const sdl_dep = b.dependency("sdl", .{
        .target = target,
        .optimize = .ReleaseFast,
    });

    const lib = b.addStaticLibrary(.{
        .name = "SDL2_mixer",
        .target = target,
        .optimize = optimize,
    });
    lib.addCSourceFiles(.{ .root = b.path("src/"), .files = &src_files });
    lib.addIncludePath(b.path("include/"));
    lib.addIncludePath(b.path("src/"));
    lib.addIncludePath(b.path("src/codecs/"));
    lib.addIncludePath(sdl_dep.artifact("SDL2").getEmittedIncludeTree());

    lib.linkLibC();
    lib.linkLibrary(sdl_dep.artifact("SDL2"));

    b.installArtifact(lib);
}
