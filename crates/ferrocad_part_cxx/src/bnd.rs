//! Bindings for bounding-box measurements and OCCT's default tolerance.

#[cxx::bridge]
mod ffi {
    unsafe extern "C++" {
        include!("ferrocad_part_cxx/include/bnd.hxx");

        type Bnd_Box = opencascade_sys::bnd::Bnd_Box;

        /// The squared diagonal of the box (`Bnd_Box::SquareExtent`).
        fn fc_bnd_box_square_extent(bnd_box: &Bnd_Box) -> f64;

        /// OCCT's default linear tolerance (`Precision::Confusion`).
        fn fc_precision_confusion() -> f64;
    }
}

pub use ffi::*;

#[cfg(test)]
mod tests {
    use super::{fc_bnd_box_square_extent, fc_precision_confusion};
    use opencascade_sys as sys;

    #[test]
    fn a_box_bounds_measure_its_diagonal() {
        let origin = sys::gp::new_point(0.0, 0.0, 0.0);
        let mut make = sys::b_rep_prim_api::BRepPrimAPI_MakeBox_new(&origin, 3.0, 4.0, 12.0);
        let mut bounds = sys::bnd::Bnd_Box_new();
        sys::b_rep_bnd_lib::BRepBndLib::Add(make.pin_mut().Shape(), bounds.pin_mut(), false);

        let extent = fc_bnd_box_square_extent(bounds.as_ref().unwrap());
        // A 3-4-12 box has a 13 diagonal; `BRepBndLib` adds the shape tolerance,
        // so compare approximately.
        assert!(
            (extent.sqrt() - 13.0).abs() < 1e-3,
            "diagonal was {}",
            extent.sqrt()
        );
        assert!((fc_precision_confusion() - 1e-7).abs() < 1e-12);
    }
}
