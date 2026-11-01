//! Typed cxx bindings for OCCT calls that `opencascade-sys` does not expose.
//!
//! This crate is the C++ boundary and is **bindings only**: one function per
//! OCCT call, named after the OCCT API, with typed results and exception
//! translation. It contains no FerroCAD/FreeCAD semantics — no element naming,
//! no history policy, no product decisions about what a shape operation should
//! mean. Those stay in `ferrocad_occt` (Rust).
//!
//! That separation is deliberate: these bindings are generic OCCT access and can
//! be donated to `opencascade-sys` (or merged into a sibling crate) without
//! carrying FerroCAD-specific behaviour.

pub mod bnd;
pub mod chfi2d;
pub mod history;
pub mod shapefix;
pub mod topology;

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
