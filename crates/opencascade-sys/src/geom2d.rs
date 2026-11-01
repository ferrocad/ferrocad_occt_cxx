pub use inner::*;

#[cxx::bridge]
mod inner {
    unsafe extern "C++" {
        include!("opencascade-sys/include/geom2d.hxx");

        type gp_Ax2d = crate::gp::gp_Ax2d;
        type gp_Pnt2d = crate::gp::gp_Pnt2d;
        type TColgp_Array1OfPnt2d = crate::t_col_gp::TColgp_Array1OfPnt2d;
        type TColStd_Array1OfReal = crate::t_col_std::TColStd_Array1OfReal;
        type TColStd_Array1OfInteger = crate::t_col_std::TColStd_Array1OfInteger;

        // Handles
        type Handle_Geom2d_Curve;
        pub fn IsNull(self: &Handle_Geom2d_Curve) -> bool;

        type Handle_Geom2d_Ellipse;
        pub fn IsNull(self: &Handle_Geom2d_Ellipse) -> bool;

        type Handle_Geom2d_TrimmedCurve;
        pub fn IsNull(self: &Handle_Geom2d_TrimmedCurve) -> bool;

        type Handle_Geom2d_BSplineCurve;
        pub fn IsNull(self: &Handle_Geom2d_BSplineCurve) -> bool;
        // End Handles

        type Geom2d_Ellipse;
        pub fn Geom2d_Ellipse_new(
            axis: &gp_Ax2d,
            major_radius: f64,
            minor_radius: f64,
        ) -> UniquePtr<Handle_Geom2d_Ellipse>;
        pub fn ellipse_to_HandleGeom2d_Curve(
            ellipse: &Handle_Geom2d_Ellipse,
        ) -> UniquePtr<Handle_Geom2d_Curve>;
        pub fn ellipse_value(ellipse: &Handle_Geom2d_Ellipse, u: f64) -> UniquePtr<gp_Pnt2d>;

        type Geom2d_Curve;
        type Geom2d_TrimmedCurve;
        pub fn Geom2d_TrimmedCurve_new(
            curve_handle: &Handle_Geom2d_Curve,
            u1: f64,
            u2: f64,
        ) -> UniquePtr<Handle_Geom2d_TrimmedCurve>;
        pub fn HandleGeom2d_TrimmedCurve_to_curve(
            trimmed_curve: &Handle_Geom2d_TrimmedCurve,
        ) -> UniquePtr<Handle_Geom2d_Curve>;

        pub fn Geom2d_BSplineCurve_new(
            poles: &TColgp_Array1OfPnt2d,
            knots: &TColStd_Array1OfReal,
            multiplicities: &TColStd_Array1OfInteger,
            degree: i32,
        ) -> Result<UniquePtr<Handle_Geom2d_BSplineCurve>>;
        pub fn Geom2d_BSplineCurve_Poles(
            curve: &Handle_Geom2d_BSplineCurve,
        ) -> &TColgp_Array1OfPnt2d;
        pub fn Geom2d_BSplineCurve_Degree(curve: &Handle_Geom2d_BSplineCurve) -> i32;
        pub fn Geom2d_BSplineCurve_IsPeriodic(curve: &Handle_Geom2d_BSplineCurve) -> bool;
    }

    impl UniquePtr<Handle_Geom2d_Ellipse> {}
    impl UniquePtr<Handle_Geom2d_Curve> {}
    impl UniquePtr<Handle_Geom2d_TrimmedCurve> {}
    impl UniquePtr<Handle_Geom2d_BSplineCurve> {}
}
