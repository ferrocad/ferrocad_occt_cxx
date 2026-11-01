pub use inner::*;

#[cxx::bridge]
mod inner {
    #[repr(u32)]
    #[derive(Debug)]
    pub enum GeomAbs_Shape {
        GeomAbs_C0,
        GeomAbs_G1,
        GeomAbs_C1,
        GeomAbs_G2,
        GeomAbs_C2,
        GeomAbs_C3,
        GeomAbs_CN,
    }

    unsafe extern "C++" {
        include!("opencascade-sys/include/geom_api.hxx");

        type gp_Pnt = crate::gp::gp_Pnt;
        type gp_Pnt2d = crate::gp::gp_Pnt2d;
        type gp_Vec = crate::gp::gp_Vec;
        type gp_Pln = crate::gp::gp_Pln;
        type Handle_TColgp_HArray1OfPnt = crate::t_col_gp::Handle_TColgp_HArray1OfPnt;
        type Handle_Geom_BSplineCurve = crate::geom::Handle_Geom_BSplineCurve;
        type Handle_Geom_Surface = crate::geom::Handle_Geom_Surface;
        type Handle_Geom_Curve = crate::geom::Handle_Geom_Curve;
        type Handle_Geom2d_Curve = crate::geom2d::Handle_Geom2d_Curve;
        type TColgp_Array2OfPnt = crate::t_col_gp::TColgp_Array2OfPnt;

        type GeomAbs_Shape;

        type GeomAPI_Interpolate;
        #[cxx_name = "construct_unique"]
        pub fn GeomAPI_Interpolate_new(
            points: &Handle_TColgp_HArray1OfPnt,
            periodic: bool,
            tolerance: f64,
        ) -> UniquePtr<GeomAPI_Interpolate>;
        pub fn Load(
            self: Pin<&mut GeomAPI_Interpolate>,
            initial_tangent: &gp_Vec,
            final_tangent: &gp_Vec,
            scale: bool,
        );
        pub fn Perform(self: Pin<&mut GeomAPI_Interpolate>);
        pub fn GeomAPI_Interpolate_Curve(
            interpolate: &GeomAPI_Interpolate,
        ) -> UniquePtr<Handle_Geom_BSplineCurve>;
        pub fn IsDone(self: &GeomAPI_Interpolate) -> bool;

        type GeomAPI_ProjectPointOnSurf;
        #[cxx_name = "construct_unique"]
        pub fn GeomAPI_ProjectPointOnSurf_new(
            origin: &gp_Pnt,
            surface: &Handle_Geom_Surface,
        ) -> UniquePtr<GeomAPI_ProjectPointOnSurf>;
        pub fn LowerDistanceParameters(self: &GeomAPI_ProjectPointOnSurf, u: &mut f64, v: &mut f64);
        pub fn NbPoints(self: &GeomAPI_ProjectPointOnSurf) -> i32;

        type GeomAPI_PointsToBSpline;
        pub fn GeomAPI_PointsToBSpline_new(
            points: &[f64],
            deg_min: i32,
            deg_max: i32,
            continuity: GeomAbs_Shape,
            tol: f64,
        ) -> Result<UniquePtr<GeomAPI_PointsToBSpline>>;
        pub fn IsDone(self: &GeomAPI_PointsToBSpline) -> bool;
        pub fn GeomAPI_PointsToBSpline_Curve(
            approx: &GeomAPI_PointsToBSpline,
        ) -> UniquePtr<Handle_Geom_BSplineCurve>;

        type GeomAPI_ProjectPointOnCurve;
        pub fn GeomAPI_ProjectPointOnCurve_new(
            point: &gp_Pnt,
            curve: &Handle_Geom_Curve,
        ) -> Result<UniquePtr<GeomAPI_ProjectPointOnCurve>>;
        pub fn NbPoints(self: &GeomAPI_ProjectPointOnCurve) -> i32;
        pub fn LowerDistanceParameter(self: &GeomAPI_ProjectPointOnCurve) -> f64;
        pub fn GeomAPI_ProjectPointOnCurve_Parameter(
            curve: &GeomAPI_ProjectPointOnCurve,
            index: i32,
        ) -> Result<f64>;

        pub fn GeomAPI_To2d(
            curve: &Handle_Geom_Curve,
            plane: &gp_Pln,
        ) -> Result<UniquePtr<Handle_Geom2d_Curve>>;

        type Geom2dAPI_InterCurveCurve;
        pub fn Geom2dAPI_InterCurveCurve_new(
            curve: &Handle_Geom2d_Curve,
            tol: f64,
        ) -> Result<UniquePtr<Geom2dAPI_InterCurveCurve>>;
        pub fn NbPoints(self: &Geom2dAPI_InterCurveCurve) -> i32;
        pub fn Geom2dAPI_InterCurveCurve_Point(
            curve: &Geom2dAPI_InterCurveCurve,
            index: i32,
        ) -> UniquePtr<gp_Pnt2d>;

        type Geom2dAPI_ProjectPointOnCurve;
        pub fn Geom2dAPI_ProjectPointOnCurve_new(
            point: &gp_Pnt2d,
            curve: &Handle_Geom2d_Curve,
            first: f64,
            last: f64,
        ) -> Result<UniquePtr<Geom2dAPI_ProjectPointOnCurve>>;
        pub fn NbPoints(self: &Geom2dAPI_ProjectPointOnCurve) -> i32;
        pub fn Geom2dAPI_ProjectPointOnCurve_Parameter(
            curve: &Geom2dAPI_ProjectPointOnCurve,
            index: i32,
        ) -> Result<f64>;

        type GeomAPI_PointsToBSplineSurface;
        #[cxx_name = "construct_unique"]
        pub fn GeomAPI_PointsToBSplineSurface_new() -> UniquePtr<GeomAPI_PointsToBSplineSurface>;
        pub fn GeomAPI_PointsToBSplineSurface_Interpolate(
            approx: Pin<&mut GeomAPI_PointsToBSplineSurface>,
            points: &TColgp_Array2OfPnt,
            periodic: bool,
        ) -> Result<()>;
        pub fn IsDone(self: &GeomAPI_PointsToBSplineSurface) -> bool;
        pub fn GeomAPI_PointsToBSplineSurface_Surface(
            approx: &GeomAPI_PointsToBSplineSurface,
        ) -> UniquePtr<Handle_Geom_Surface>;
    }
}
