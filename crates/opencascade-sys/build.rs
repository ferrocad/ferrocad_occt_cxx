/// Minimum compatible version of OpenCASCADE library (major, minor)
///
/// Pre-installed OpenCASCADE library will be checked for compatibility using
/// these bounds: OCCT 7.8 and later 7.x releases are supported, as is every
/// 8.x release. Anything older (6.x) or newer (9.x and up) is rejected.
const OCCT_VERSION: (u8, u8) = (7, 8);

/// Highest OpenCASCADE major version this crate is prepared for. The C++
/// bridge is built as C++17 and `include/occt8_handle_compat.hxx` restores the
/// `Handle_*` names OCCT 8 removed from the class headers.
const OCCT_MAX_MAJOR: u8 = 8;

/// The list of used OpenCASCADE libraries which needs to be linked with.
const OCCT_LIBS: &[&str] = &[
    "TKMath",
    "TKernel",
    "TKDE",
    "TKFeat",
    "TKGeomBase",
    "TKG2d",
    "TKG3d",
    "TKTopAlgo",
    "TKGeomAlgo",
    "TKBRep",
    "TKPrim",
    "TKDESTEP",
    "TKDEIGES",
    "TKDESTL",
    "TKMesh",
    "TKShHealing",
    "TKFillet",
    "TKBool",
    "TKBO",
    "TKOffset",
    "TKXSBase",
    "TKCAF",
    "TKLCAF",
    "TKXCAF",
];

/// The OCCT toolkits present in the prebuilt wasm kernel (cadrum's
/// `occt-8_0_1_rev3-wasm32_unknown_unknown`). It is headless: no visualization,
/// OCAF, IGES, STL or BRepFeat toolkits, so it is a subset of `OCCT_LIBS`.
/// `cargo check` compiles against the full header set; a final link only resolves
/// what these archives provide.
const OCCT_WASM_LIBS: &[&str] = &[
    "TKernel",
    "TKMath",
    "TKBRep",
    "TKTopAlgo",
    "TKPrim",
    "TKBO",
    "TKBool",
    "TKShHealing",
    "TKMesh",
    "TKGeomBase",
    "TKGeomAlgo",
    "TKG3d",
    "TKG2d",
    "TKXSBase",
    "TKDE",
    "TKDECascade",
    "TKOffset",
    "TKFillet",
    "TKDESTEP",
];

/// Whether the detected OCCT `major`.`minor` is inside the supported range:
/// `OCCT_VERSION.0` from `OCCT_VERSION.1` upwards, or any `OCCT_MAX_MAJOR` release.
fn is_supported_occt_version(major: u8, minor: u8) -> bool {
    // 7.8 and later 7.x releases.
    if major == OCCT_VERSION.0 {
        minor >= OCCT_VERSION.1
    } else {
        major == OCCT_MAX_MAJOR
    }
}

fn main() {
    // The package is `ferrocad_occt_cxx`, but every bridge source and the
    // Windows include path still spell `opencascade-sys/include/…`. Pin cxx's
    // include prefix to the historical name so the rename is transparent to
    // the generated C++ and to downstream crates.
    cxx_build::CFG.include_prefix = "opencascade-sys";

    let target = std::env::var("TARGET").expect("No TARGET environment variable defined");
    let is_windows = target.to_lowercase().contains("windows");
    let is_windows_gnu = target.to_lowercase().contains("windows-gnu");

    let is_wasm = target.starts_with("wasm32");
    let occt_config = if is_wasm {
        OcctConfig::detect_wasm()
    } else {
        OcctConfig::detect()
    };

    println!("cargo:rustc-link-search=native={}", occt_config.library_dir.to_str().unwrap());

    if is_wasm {
        // Prebuilt wasm kernel: static archives, plus the libc++/EH runtime the
        // tarball ships for its wasi-sdk build. `libc++.a` is linked by
        // `link-cplusplus` as `-lc++` through the search path above.
        for lib in OCCT_WASM_LIBS {
            println!("cargo:rustc-link-lib=static={lib}");
        }
        for lib in wasm_runtime_libs(&occt_config.library_dir) {
            println!("cargo:rustc-link-lib=static={lib}");
        }
    } else {
        let lib_type = if occt_config.is_dynamic { "dylib" } else { "static" };
        for lib in OCCT_LIBS {
            println!("cargo:rustc-link-lib={lib_type}={lib}");
        }
    }

    if is_windows {
        println!("cargo:rustc-link-lib=dylib=user32");
        // MSVC only: TKernel's
        // OSD_* (file protection, process user name, registry-based debug
        // flags) needs the Win32 security/registry API, which isn't pulled in
        // by anything else here. Without it, linking any binary against
        // opencascade-sys fails with ~23 unresolved externals (SetFileSecurityW,
        // OpenProcessToken, GetTokenInformation, RegOpenKeyExW, ...).
        println!("cargo:rustc-link-lib=dylib=advapi32");
    }

    // TODO(bschwind) - Iterate over the src/ directory to populate this.
    let rust_bridges = [
        "src/b_rep.rs",
        "src/b_rep_adaptor.rs",
        "src/b_rep_algo.rs",
        "src/b_rep_algo_api.rs",
        "src/b_rep_bnd_lib.rs",
        "src/b_rep_builder_api.rs",
        "src/b_rep_check.rs",
        "src/b_rep_class.rs",
        "src/b_rep_extrema.rs",
        "src/b_rep_feat.rs",
        "src/b_rep_fill.rs",
        "src/b_rep_fillet_api.rs",
        "src/b_rep_g_prop.rs",
        "src/b_rep_int_curve_surface.rs",
        "src/b_rep_l_prop.rs",
        "src/b_rep_lib.rs",
        "src/b_rep_mesh.rs",
        "src/b_rep_offset_api.rs",
        "src/b_rep_prim_api.rs",
        "src/b_rep_proj.rs",
        "src/b_rep_tools.rs",
        "src/b_rep_top_adaptor.rs",
        "src/bin_tools.rs",
        "src/bnd.rs",
        "src/bop_algo.rs",
        "src/bspl_clib.rs",
        "src/chfi2d.rs",
        "src/cs_lib.rs",
        "src/g_prop.rs",
        "src/gc.rs",
        "src/gc_pnts.rs",
        "src/geom.rs",
        "src/geom2d.rs",
        "src/geom2d_convert.rs",
        "src/geom_abs.rs",
        "src/geom_adaptor.rs",
        "src/geom_api.rs",
        "src/geom_convert.rs",
        "src/geom_proj_lib.rs",
        "src/gp.rs",
        "src/if_select.rs",
        "src/iges_control.rs",
        "src/law.rs",
        "src/message.rs",
        "src/poly.rs",
        "src/precision.rs",
        "src/shape_analysis.rs",
        "src/shape_construct.rs",
        "src/shape_fix.rs",
        "src/shape_upgrade.rs",
        "src/standard.rs",
        "src/step_control.rs",
        "src/stl_api.rs",
        "src/t_col_gp.rs",
        "src/t_col_std.rs",
        "src/top_abs.rs",
        "src/top_exp.rs",
        "src/top_loc.rs",
        "src/top_tools.rs",
        "src/topo_ds.rs",
    ];

    // The bridge headers and the OCCT-8 compatibility shim are build inputs too.
    // Without this, a header-only edit is invisible to cargo and links against
    // stale objects (the bridge loop below only tracks the `.rs` files).
    println!("cargo:rerun-if-changed=include");

    let mut build = cxx_build::bridges(rust_bridges);

    if is_windows_gnu {
        build.define("OCC_CONVERT_SIGNALS", "TRUE");
    }

    if is_wasm {
        // The prebuilt kernel uses the legacy wasm-EH encoding of the cross
        // image's rebuilt sysroot; the bridge must match it or the EH metadata
        // does not link. No-op without `-fwasm-exceptions`.
        build.flag("-mllvm").flag("-wasm-use-legacy-eh=true");
    }

    if let "windows" = std::env::consts::OS {
        let current = std::env::current_dir().unwrap();
        build.include(current.parent().unwrap());
    }

    build
        .cpp(true)
        // OCCT 8 requires C++17 (`BUILD_CPP_STANDARD` defaults to C++17 with
        // `CMAKE_CXX_STANDARD_REQUIRED ON`) and its headers use `inline constexpr`.
        // `cc::Build::std` emits `/std:c++17` on MSVC instead of a raw `-std=` flag.
        .std("c++17")
        .define("_USE_MATH_DEFINES", "TRUE")
        .include(occt_config.include_dir)
        .include("include")
        .compile("rust-occt");

    println!("cargo:rustc-link-lib=static=rust-occt");

    for bridge in rust_bridges {
        println!("cargo:rerun-if-changed={bridge}");
    }
}

/// The `libcadrum_*.a` archives in the wasm tarball (`unwind`, `c++abi`, `c`),
/// which carry the libc++/wasm-EH runtime the prebuilt OCCT was built against.
fn wasm_runtime_libs(library_dir: &std::path::Path) -> Vec<String> {
    let Ok(entries) = std::fs::read_dir(library_dir) else {
        return Vec::new();
    };
    let mut names: Vec<String> = entries
        .flatten()
        .filter_map(|entry| entry.file_name().to_str().map(str::to_owned))
        .filter(|name| name.starts_with("libcadrum") && name.ends_with(".a"))
        .map(|name| name["lib".len()..name.len() - ".a".len()].to_owned())
        .collect();
    names.sort();
    names
}

struct OcctConfig {
    include_dir: std::path::PathBuf,
    library_dir: std::path::PathBuf,
    is_dynamic: bool,
}

impl OcctConfig {
    /// The prebuilt wasm32 kernel (cadrum's
    /// `occt-8_0_1_rev3-wasm32_unknown_unknown`).
    ///
    /// There is no CMake probe on wasm: the tarball is an install tree, so the
    /// layout is known. Point `OCCT_WASM_ROOT` at the extracted directory. The
    /// tarball is built with wasi-sdk 33 (`--target=wasm32-wasip1`,
    /// `-fwasm-exceptions`), so the bridge must be compiled with the same
    /// toolchain; the `ghcr.io/lzpel/cross-wasm32-unknown-unknown` image provides
    /// it.
    fn detect_wasm() -> Self {
        println!("cargo:rerun-if-env-changed=OCCT_WASM_ROOT");
        let root = std::env::var_os("OCCT_WASM_ROOT").unwrap_or_else(|| {
            panic!(
                "building for wasm32 needs a prebuilt OCCT kernel.\n\
                 Download https://github.com/lzpel/cadrum/releases/download/occt-8_0_1_rev3/\
                 occt-8_0_1_rev3-wasm32_unknown_unknown.tar.gz, extract it, and set \
                 OCCT_WASM_ROOT to the extracted directory. Build it inside the \
                 ghcr.io/lzpel/cross-wasm32-unknown-unknown image."
            )
        });
        let root = std::path::PathBuf::from(root);
        let include_dir = root.join("include").join("opencascade");
        let library_dir = root.join("lib");
        if !library_dir.join("libTKernel.a").is_file() {
            panic!(
                "OCCT_WASM_ROOT ({}) does not look like the prebuilt wasm kernel: \
                 expected lib/libTKernel.a and include/opencascade",
                root.display()
            );
        }
        let version = std::fs::read_to_string(include_dir.join("Standard_Version.hxx"))
            .expect("the wasm OCCT prefix is missing Standard_Version.hxx");
        let number = |name: &str| -> Option<u8> {
            let prefix = format!("#define {name}");
            version.lines().find_map(|line| {
                line.trim()
                    .strip_prefix(&prefix)
                    .and_then(|rest| rest.split_whitespace().next())
                    .and_then(|value| value.parse().ok())
            })
        };
        let major = number("OCC_VERSION_MAJOR").expect("OCC_VERSION_MAJOR missing");
        let minor = number("OCC_VERSION_MINOR").expect("OCC_VERSION_MINOR missing");
        if !is_supported_occt_version(major, minor) {
            panic!(
                "the wasm OCCT kernel is {major}.{minor}, but {}.{}+ or {}.x is required",
                OCCT_VERSION.0, OCCT_VERSION.1, OCCT_MAX_MAJOR
            );
        }
        Self {
            include_dir,
            library_dir,
            is_dynamic: false,
        }
    }

    /// Find OpenCASCADE library using cmake
    fn detect() -> Self {
        println!("cargo:rerun-if-env-changed=DEP_OCCT_ROOT");
        // A different OCCT prefix must rebuild the bridge objects. Without these,
        // cargo treats the crate as fresh and silently reuses objects compiled
        // against another OCCT version.
        for var in ["OpenCASCADE_DIR", "OCCT_INCLUDE_DIR", "CASROOT", "OCCT_ROOT"] {
            println!("cargo:rerun-if-env-changed={var}");
        }

        // There is no in-tree OCCT build: this crate only ever links a kernel
        // that already exists (an install prefix, or the prebuilt wasm one).
        let dst = std::panic::catch_unwind(|| {
            cmake::Config::new("OCCT").register_dep("occt").build()
        })
        .expect(
            "Pre-installed OpenCASCADE library not found. Point OpenCASCADE_DIR at the \
             directory containing OpenCASCADEConfig.cmake and OCCT_INCLUDE_DIR at the \
             matching include directory (see the README); this fork does not build \
             OCCT from source.",
        );

        let cfg = std::fs::read_to_string(dst.join("share").join("occ_info.txt"))
            .expect("Something went wrong when detecting OpenCASCADE library.");

        let mut version_major: Option<u8> = None;
        let mut version_minor: Option<u8> = None;
        let mut include_dir: Option<std::path::PathBuf> = None;
        let mut library_dir: Option<std::path::PathBuf> = None;
        let mut is_dynamic: bool = false;

        for line in cfg.lines() {
            if let Some((var, val)) = line.split_once('=') {
                match var {
                    "VERSION_MAJOR" => version_major = val.parse().ok(),
                    "VERSION_MINOR" => version_minor = val.parse().ok(),
                    "INCLUDE_DIR" => include_dir = val.parse().ok(),
                    "LIBRARY_DIR" => library_dir = val.parse().ok(),
                    "BUILD_SHARED_LIBS" => is_dynamic = val == "ON",
                    _ => (),
                }
            }
        }

        if let (Some(version_major), Some(version_minor), Some(include_dir), Some(library_dir)) =
            (version_major, version_minor, include_dir, library_dir)
        {
            if !is_supported_occt_version(version_major, version_minor) {
                panic!("Pre-installed OpenCASCADE library found but version is not met (found {}.{} but {}.{}+ or {}.x required). Please provide the required version.",
                       version_major, version_minor, OCCT_VERSION.0, OCCT_VERSION.1, OCCT_MAX_MAJOR);
            }

            Self { include_dir, library_dir, is_dynamic }
        } else {
            panic!("OpenCASCADE library found but something wrong with config.");
        }
    }
}
