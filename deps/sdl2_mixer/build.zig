const std = @import("std");

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

const c_flags = [_][]const u8{
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

    const emscripten_include = b.option(std.Build.LazyPath, "emscripten_include", "Emscripten sysroot include directory");
    const sdl_dep = b.dependency("sdl", .{
        .target = target,
        .optimize = .fast,
        .emscripten_include = emscripten_include,
    });
    const modplug_dep = b.dependency("libmodplug", .{
        .target = target,
        .optimize = .fast, // there are some unsound code in this lib, compiling with safe will result in runtime errors
    });

    const lib = b.addLibrary(.{
        .name = "SDL2_mixer",
        .root_module = b.createModule(.{
            .target = target,
            .optimize = optimize,
        }),
    });
    lib.root_module.addCSourceFiles(.{ .root = b.path("src/"), .files = &src_files, .flags = if (target.result.os.tag == .emscripten) &(c_flags ++ .{"-fno-sanitize=undefined"}) else &c_flags });
    lib.root_module.addIncludePath(b.path("include/"));
    lib.root_module.addIncludePath(b.path("src/"));
    lib.root_module.addIncludePath(b.path("src/codecs/"));
    lib.root_module.addIncludePath(sdl_dep.artifact("SDL2").getEmittedIncludeTree());
    lib.root_module.addIncludePath(modplug_dep.artifact("libmodplug").getEmittedIncludeTree());

    lib.root_module.link_libc = true;
    lib.root_module.linkLibrary(sdl_dep.artifact("SDL2"));
    lib.root_module.linkLibrary(modplug_dep.artifact("libmodplug"));

    lib.installHeadersDirectory(b.path("include"), "", .{});
    b.installArtifact(lib);
}
