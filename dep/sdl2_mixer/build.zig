const std = @import("std");
const builtin = @import("builtin");

const src_files = [_][]const u8{
    "codecs/load_aiff.c",
    "codecs/load_voc.c",
    "codecs/mp3utils.c",
    "codecs/music_cmd.c",
    "codecs/music_drflac.c",
    "codecs/music_minimp3.c",
    "codecs/music_modplug.c",
    "codecs/music_ogg_stb.c",
    "codecs/music_timidity.c",
    "codecs/timidity/common.c",
    "codecs/timidity/instrum.c",
    "codecs/timidity/mix.c",
    "codecs/timidity/output.c",
    "codecs/timidity/playmidi.c",
    "codecs/timidity/readmidi.c",
    "codecs/timidity/resample.c",
    "codecs/timidity/tables.c",
    "codecs/timidity/timidity.c",
    "codecs/music_wav.c",
    "effect_position.c",
    "effect_stereoreverse.c",
    "effects_internal.c",
    "mixer.c",
    "music.c",
    "utils.c",
};

const c_flags: []const []const u8 = &.{
    "-DMUSIC_CMD",
    "-DMUSIC_WAV",
    "-DMUSIC_FLAC_DRFLAC",
    "-DMUSIC_OGG",
    "-DOGG_USE_STB",
    "-DMUSIC_MP3_MINIMP3",
    "-DMUSIC_MOD_MODPLUG",
    "-DMUSIC_MID_TIMIDITY",
};

pub fn build(b: *std.Build) !void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const sdl_dep = b.dependency("sdl", .{
        .target = target,
        .optimize = .ReleaseFast,
    });
    const modplug_dep = b.dependency("libmodplug", .{
        .target = target,
        .optimize = .ReleaseFast, // there are some unsound coding practices in this lib, don't compile with safe
    });

    const lib = b.addStaticLibrary(.{
        .name = "SDL2_mixer",
        .target = target,
        .optimize = optimize,
    });
    lib.addCSourceFiles(.{ .root = b.path("src/"), .files = &src_files, .flags = c_flags });
    lib.addIncludePath(b.path("include/"));
    lib.addIncludePath(b.path("src/"));
    lib.addIncludePath(b.path("src/codecs/"));
    lib.addIncludePath(sdl_dep.artifact("SDL2").getEmittedIncludeTree());
    lib.addIncludePath(modplug_dep.artifact("libmodplug").getEmittedIncludeTree());

    lib.linkLibC();
    lib.linkLibrary(sdl_dep.artifact("SDL2"));
    lib.linkLibrary(modplug_dep.artifact("libmodplug"));

    lib.installHeadersDirectory(b.path("include"), "", .{});
    b.installArtifact(lib);
}
