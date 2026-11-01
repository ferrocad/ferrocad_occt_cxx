//! Compile the typed cxx bridge over the OCCT Part layer.
//!
//! This crate owns every OCCT call that `opencascade-sys` does not expose, with
//! OCCT's failure type translated to a Rust `Result` at the C++ boundary. It
//! needs the OCCT headers to compile the bridge, but links no OCCT libraries
//! itself: `opencascade-sys` emits those link directives.
//!
//! The include directory is `OCCT_INCLUDE_DIR` when set. Otherwise it is
//! discovered from `OCCT_ROOT`/`CASROOT`/`OpenCASCADE_DIR`, a `.occt/prefix`
//! below the workspace or current directory, or a common system prefix.

use std::path::{Path, PathBuf};

fn main() {
    for var in [
        "OCCT_INCLUDE_DIR",
        "OCCT_ROOT",
        "CASROOT",
        "OpenCASCADE_DIR",
    ] {
        println!("cargo:rerun-if-env-changed={var}");
    }
    for file in [
        "include/gtransform.hxx",
        "include/bnd.hxx",
        "include/chfi2d.hxx",
        "include/curve.hxx",
        "include/geom2d.hxx",
        "include/history.hxx",
        "include/ops.hxx",
        "include/part_ops.hxx",
        "include/shape_ops.hxx",
        "include/shapefix.hxx",
        "include/surface_ops.hxx",
        "include/topology.hxx",
        "src/bnd.rs",
        "src/chfi2d.rs",
        "src/history.rs",
        "src/lib.rs",
        "src/ops.rs",
        "src/shapefix.rs",
        "src/surface_ops.rs",
        "src/topology.rs",
    ] {
        println!("cargo:rerun-if-changed={file}");
    }

    let include = find_include().unwrap_or_else(|| {
        panic!(
            "could not find the OCCT headers. Set OCCT_INCLUDE_DIR to the OCCT \
             'include/opencascade' directory, or OCCT_ROOT/CASROOT/OpenCASCADE_DIR."
        )
    });

    cxx_build::bridges([
        "src/lib.rs",
        "src/bnd.rs",
        "src/chfi2d.rs",
        "src/shapefix.rs",
        "src/history.rs",
        "src/ops.rs",
        "src/surface_ops.rs",
        "src/topology.rs",
    ])
        .include(&include)
        .std("c++14")
        .compile("ferrocad-part-cxx");
}

/// Find the directory that contains `Standard_Version.hxx`.
fn find_include() -> Option<PathBuf> {
    if let Ok(value) = std::env::var("OCCT_INCLUDE_DIR") {
        if let Some(found) = normalize(PathBuf::from(value)) {
            return Some(found);
        }
        println!(
            "cargo:warning=OCCT_INCLUDE_DIR does not contain Standard_Version.hxx; \
             searching the known prefixes"
        );
    }

    for var in ["OCCT_ROOT", "CASROOT", "OpenCASCADE_DIR"] {
        if let Ok(value) = std::env::var(var) {
            if let Some(found) = under(Path::new(&value)) {
                return Some(found);
            }
        }
    }

    if let Some(workspace) = Path::new(env!("CARGO_MANIFEST_DIR")).ancestors().nth(2) {
        if let Some(found) = normalize(workspace.join(".occt/prefix")) {
            return Some(found);
        }
    }
    if let Ok(cwd) = std::env::current_dir() {
        for ancestor in cwd.ancestors() {
            if let Some(found) = normalize(ancestor.join(".occt/prefix")) {
                return Some(found);
            }
        }
    }

    for prefix in ["/usr", "/usr/local", "/opt/homebrew", "/opt/local"] {
        if let Some(found) = normalize(PathBuf::from(prefix)) {
            return Some(found);
        }
    }
    None
}

/// A path that is a prefix, an include directory, or a CMake config directory.
fn under(path: &Path) -> Option<PathBuf> {
    if let Some(found) = normalize(path.to_path_buf()) {
        return Some(found);
    }
    for ancestor in path.ancestors() {
        if let Some(found) = normalize(ancestor.to_path_buf()) {
            return Some(found);
        }
    }
    None
}

/// Normalize `path` to a directory containing `Standard_Version.hxx`.
fn normalize(path: PathBuf) -> Option<PathBuf> {
    let candidates = [
        path.clone(),
        path.join("opencascade"),
        path.join("include").join("opencascade"),
    ];
    candidates
        .into_iter()
        .find(|candidate| candidate.join("Standard_Version.hxx").is_file())
}
