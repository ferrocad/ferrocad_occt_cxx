//! Typed cxx bindings for the FerroCAD Part layer.
//!
//! This crate owns the C++ boundary. Every OCCT call that `opencascade-sys`
//! does not expose lives here, with OCCT's failure type translated to a Rust
//! `Result` before it crosses cxx's `noexcept` shim. FerroCAD policy —
//! validation, composition, history and error mapping — belongs in
//! `ferrocad_occt`, not here.

#[cxx::bridge]
mod ffi {
    unsafe extern "C++" {
        include!("ferrocad_part_cxx/include/gtransform.hxx");

        type TopoDS_Shape = opencascade_sys::topo_ds::TopoDS_Shape;

        /// Apply a row-major affine 4x4 `matrix` to `shape`.
        fn gtransform(shape: &TopoDS_Shape, matrix: &[f64]) -> Result<UniquePtr<TopoDS_Shape>>;
    }
}

pub use ffi::gtransform;

#[cfg(test)]
mod tests {
    use super::gtransform;
    use opencascade_sys as ffi;

    #[test]
    fn gtransform_scales_a_box() {
        let origin = ffi::gp::new_point(0.0, 0.0, 0.0);
        let mut make = ffi::b_rep_prim_api::BRepPrimAPI_MakeBox_new(&origin, 1.0, 2.0, 3.0);
        let matrix = [
            2.0, 0.0, 0.0, 0.0, //
            0.0, 3.0, 0.0, 0.0, //
            0.0, 0.0, 4.0, 0.0, //
            0.0, 0.0, 0.0, 1.0,
        ];
        let transformed =
            gtransform(make.pin_mut().Shape(), &matrix).expect("affine transform");
        assert!(!transformed.is_null());
    }
}
