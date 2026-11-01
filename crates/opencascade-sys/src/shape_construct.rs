pub use inner::*;

#[cxx::bridge]
mod inner {
    unsafe extern "C++" {
        include!("opencascade-sys/include/shape_construct.hxx");

        type Handle_Geom_Curve = crate::geom::Handle_Geom_Curve;
        type Handle_Geom_BSplineCurve = crate::geom::Handle_Geom_BSplineCurve;

        type ShapeConstruct_Curve;
        #[cxx_name = "construct_unique"]
        pub fn ShapeConstruct_Curve_new() -> UniquePtr<ShapeConstruct_Curve>;
        pub fn ShapeConstruct_Curve_ConvertToBSpline(
            curve: &ShapeConstruct_Curve,
            source: &Handle_Geom_Curve,
            first: f64,
            last: f64,
            precision: f64,
        ) -> Result<UniquePtr<Handle_Geom_BSplineCurve>>;
    }
}
