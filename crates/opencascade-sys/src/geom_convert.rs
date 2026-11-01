pub use inner::*;

#[cxx::bridge]
mod inner {
    unsafe extern "C++" {
        include!("opencascade-sys/include/geom_convert.hxx");

        type Handle_Geom_Curve = crate::geom::Handle_Geom_Curve;
        type Handle_Geom_BSplineCurve = crate::geom::Handle_Geom_BSplineCurve;

        pub fn GeomConvert_CurveToBSplineCurve(
            curve: &Handle_Geom_Curve,
        ) -> Result<UniquePtr<Handle_Geom_BSplineCurve>>;
    }
}
