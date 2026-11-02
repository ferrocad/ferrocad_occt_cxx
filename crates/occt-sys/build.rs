use std::{
    env::var,
    path::{Path, PathBuf},
};

fn main() {
    // The `builtin` feature compiles OCCT from this checkout. It is deliberately
    // *not* a git submodule: Cargo fetches submodules of git dependencies
    // unconditionally, so every consumer of `ferrocad_occt_cxx` would clone the
    // whole upstream kernel even though only `builtin` needs it.
    println!("cargo:rerun-if-env-changed=OCCT_SRC_DIR");
    let default = Path::new(&var("CARGO_MANIFEST_DIR").unwrap()).join("OCCT");
    let src = var("OCCT_SRC_DIR").map(PathBuf::from).unwrap_or(default);
    println!("cargo:rustc-env=OCCT_SRC_DIR={}", src.display());
    println!(
        "cargo:rustc-env=OCCT_PATCH_DIR={}",
        Path::new(&var("CARGO_MANIFEST_DIR").unwrap()).join("patch").to_string_lossy()
    );
}
