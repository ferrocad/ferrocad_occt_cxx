use std::{
    env::var,
    path::{Path, PathBuf},
};

const LIB_DIR: &str = "lib";
const INCLUDE_DIR: &str = "include";

/// Get the path to the OCCT library installation directory to be
/// used in build scripts.
///
/// Only valid during build (`cargo clean` removes these files).
pub fn occt_path() -> PathBuf {
    // moves the output into target/TARGET/OCCT
    // this way its less likely to be rebuilt without a cargo clean
    Path::new(&var("OUT_DIR").expect("missing OUT_DIR")).join("../../../../OCCT")
}

/// Build the OCCT library (the `builtin` feature).
///
/// The source tree is `OCCT_SRC_DIR` if set, else `crates/occt-sys/OCCT`. It is
/// not a git submodule (Cargo would fetch it for every consumer, including those
/// that link a prebuilt kernel), so it must be checked out on demand; the
/// assertion below says how when it is missing.
pub fn build_occt() {
    let src = Path::new(env!("OCCT_SRC_DIR"));
    assert!(
        src.join("CMakeLists.txt").exists(),
        "the `builtin` feature builds OCCT from source, but there is no OCCT checkout at {}.\n\
         Fetch one and point OCCT_SRC_DIR at it:\n\n  \
         git clone --depth 1 --branch V8_0_1 https://github.com/Open-Cascade-SAS/OCCT.git {}\n\n  \
         OCCT_SRC_DIR={} cargo build --features builtin\n\n\
         Without `builtin`, the build links the OCCT that CMake finds (see the README).",
        src.display(),
        src.display(),
        src.display(),
    );
    cmake::Config::new(src)
        .define("BUILD_PATCH", Path::new(env!("OCCT_PATCH_DIR")))
        .define("BUILD_LIBRARY_TYPE", "Static")
        .define("BUILD_MODULE_ApplicationFramework", "FALSE")
        .define("BUILD_MODULE_Draw", "FALSE")
        .define("USE_D3D", "FALSE")
        .define("USE_DRACO", "FALSE")
        .define("USE_EIGEN", "FALSE")
        .define("USE_FFMPEG", "FALSE")
        .define("USE_FREEIMAGE", "FALSE")
        .define("USE_FREETYPE", "FALSE")
        .define("USE_GLES2", "FALSE")
        .define("USE_OPENGL", "FALSE")
        .define("USE_OPENVR", "FALSE")
        .define("USE_RAPIDJSON", "FALSE")
        .define("USE_TBB", "FALSE")
        .define("USE_TCL", "FALSE")
        .define("USE_TK", "FALSE")
        .define("USE_VTK", "FALSE")
        .define("USE_XLIB", "FALSE")
        .define("INSTALL_DIR_LIB", LIB_DIR)
        .define("INSTALL_DIR_INCLUDE", INCLUDE_DIR)
        .profile("Release")
        .out_dir(occt_path())
        .build();
}
