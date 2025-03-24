const std = @import("std");
const Build = std.Build;

const src_files = [_][]const u8{
    "fastmix.cpp",
    "load_669.cpp",
    "load_abc.cpp",
    "load_amf.cpp",
    "load_ams.cpp",
    "load_dbm.cpp",
    "load_dmf.cpp",
    "load_dsm.cpp",
    "load_far.cpp",
    "load_it.cpp",
    "load_j2b.cpp",
    "load_mdl.cpp",
    "load_med.cpp",
    "load_mid.cpp",
    "load_mod.cpp",
    "load_mt2.cpp",
    "load_mtm.cpp",
    "load_okt.cpp",
    "load_pat.cpp",
    "load_psm.cpp",
    "load_ptm.cpp",
    "load_s3m.cpp",
    "load_stm.cpp",
    "load_ult.cpp",
    "load_umx.cpp",
    "load_wav.cpp",
    "load_xm.cpp",
    "mmcmp.cpp",
    "modplug.cpp",
    "snd_dsp.cpp",
    "snd_flt.cpp",
    "snd_fx.cpp",
    "sndfile.cpp",
    "sndmix.cpp",
};

const c_flags: []const []const u8 = &.{
    "-DMODPLUG_BUILD",
    "-DMODPLUG_STATIC",
    "-DHAVE_STDINT_H",
    "-DHAVE_STRINGS_H",
    "-DHAVE_SINF",
};

pub fn build(b: *Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const lib = b.addLibrary(.{
        .name = "libmodplug",
        .root_module = b.createModule(.{
            .target = target,
            .optimize = optimize,
        }),
    });
    lib.addCSourceFiles(.{ .root = b.path("src/"), .files = &src_files, .flags = c_flags });
    lib.addIncludePath(b.path("src/libmodplug/"));

    lib.linkLibC();
    lib.linkLibCpp();

    lib.installHeader(b.path("src/modplug.h"), "libmodplug/modplug.h");
    b.installArtifact(lib);
}
