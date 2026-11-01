pub use inner::*;

#[cxx::bridge]
mod inner {
    unsafe extern "C++" {
        include!("opencascade-sys/include/geom2d_convert.hxx");

        type Handle_Geom2d_Curve = crate::geom2d::Handle_Geom2d_Curve;

        pub fn Geom2dConvert_CurveToBSplineCurve(
            curve: &Handle_Geom2d_Curve,
        ) -> Result<UniquePtr<Handle_Geom2d_Curve>>;
    }
}
