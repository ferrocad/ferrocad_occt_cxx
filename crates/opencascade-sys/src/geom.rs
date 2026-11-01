pub use inner::*;

#[cxx::bridge]
mod inner {
    unsafe extern "C++" {
        include!("opencascade-sys/include/geom.hxx");

        type gp_Ax2 = crate::gp::gp_Ax2;
        type gp_Ax3 = crate::gp::gp_Ax3;
        type gp_Pnt = crate::gp::gp_Pnt;
        type gp_Pln = crate::gp::gp_Pln;
        type gp_Dir = crate::gp::gp_Dir;
        type gp_Trsf = crate::gp::gp_Trsf;
        type gp_Lin = crate::gp::gp_Lin;
        type gp_Circ = crate::gp::gp_Circ;
        type gp_Elips = crate::gp::gp_Elips;
        type gp_Hypr = crate::gp::gp_Hypr;
        type gp_Parab = crate::gp::gp_Parab;
        type TColgp_Array1OfPnt = crate::t_col_gp::TColgp_Array1OfPnt;
        type TColgp_Array2OfPnt = crate::t_col_gp::TColgp_Array2OfPnt;
        type TColgp_HArray1OfPnt = crate::t_col_gp::TColgp_HArray1OfPnt;
        type TColStd_Array1OfReal = crate::t_col_std::TColStd_Array1OfReal;
        type TColStd_Array1OfInteger = crate::t_col_std::TColStd_Array1OfInteger;
        type TColStd_Array2OfReal = crate::t_col_std::TColStd_Array2OfReal;
        type Handle_Standard_Type = crate::standard::Handle_Standard_Type;
        type GeomAbs_Shape = crate::geom_api::GeomAbs_Shape;

        // Handles
        type Handle_Geom_Curve;
        pub fn IsNull(self: &Handle_Geom_Curve) -> bool;
        pub fn HandleGeomCurve_Value(curve: &Handle_Geom_Curve, u: f64) -> UniquePtr<gp_Pnt>;
        pub fn HandleGeomCurve_FirstParameter(curve: &Handle_Geom_Curve) -> f64;
        pub fn HandleGeomCurve_LastParameter(curve: &Handle_Geom_Curve) -> f64;
        pub fn HandleGeomCurve_Transformed(
            curve: &Handle_Geom_Curve,
            transform: &gp_Trsf,
        ) -> Result<UniquePtr<Handle_Geom_Curve>>;

        type Handle_Geom_Line;
        pub fn IsNull(self: &Handle_Geom_Line) -> bool;

        type Handle_Geom_Circle;
        pub fn IsNull(self: &Handle_Geom_Circle) -> bool;

        type Handle_Geom_Ellipse;
        pub fn IsNull(self: &Handle_Geom_Ellipse) -> bool;

        type Handle_Geom_Hyperbola;
        pub fn IsNull(self: &Handle_Geom_Hyperbola) -> bool;

        type Handle_Geom_Parabola;
        pub fn IsNull(self: &Handle_Geom_Parabola) -> bool;

        type Handle_Geom_Conic;
        pub fn IsNull(self: &Handle_Geom_Conic) -> bool;

        type Handle_Geom_OffsetCurve;
        pub fn IsNull(self: &Handle_Geom_OffsetCurve) -> bool;

        type Handle_Geom_BSplineCurve;
        pub fn IsNull(self: &Handle_Geom_BSplineCurve) -> bool;

        type Handle_Geom_BezierCurve;
        pub fn IsNull(self: &Handle_Geom_BezierCurve) -> bool;

        type Handle_Geom_TrimmedCurve;
        pub fn IsNull(self: &Handle_Geom_TrimmedCurve) -> bool;

        type Handle_Geom_Surface;
        pub fn IsNull(self: &Handle_Geom_Surface) -> bool;
        pub fn Handle_Geom_Surface_new() -> UniquePtr<Handle_Geom_Surface>;
        pub fn DynamicType(surface: &Handle_Geom_Surface) -> &Handle_Standard_Type;

        type Handle_Geom_BezierSurface;
        pub fn IsNull(self: &Handle_Geom_BezierSurface) -> bool;

        type Handle_Geom_Plane;
        pub fn IsNull(self: &Handle_Geom_Plane) -> bool;
        pub fn Geom_Plane_new(plane: &gp_Pln) -> UniquePtr<Handle_Geom_Plane>;
        pub fn plane_to_surface(plane_handle: &Handle_Geom_Plane) -> UniquePtr<Handle_Geom_Surface>;

        type Handle_Geom_CylindricalSurface;
        pub fn IsNull(self: &Handle_Geom_CylindricalSurface) -> bool;

        type Handle_Geom_ConicalSurface;
        pub fn IsNull(self: &Handle_Geom_ConicalSurface) -> bool;

        type Handle_Geom_SphericalSurface;
        pub fn IsNull(self: &Handle_Geom_SphericalSurface) -> bool;

        type Handle_Geom_ToroidalSurface;
        pub fn IsNull(self: &Handle_Geom_ToroidalSurface) -> bool;

        type Handle_Geom_BSplineSurface;
        pub fn IsNull(self: &Handle_Geom_BSplineSurface) -> bool;
        // End Handles

        type Geom_TrimmedCurve;

        type Geom_CylindricalSurface;
        pub fn Geom_CylindricalSurface_new(
            axis: &gp_Ax3,
            radius: f64,
        ) -> UniquePtr<Handle_Geom_CylindricalSurface>;
        pub fn cylinder_to_surface(
            cylinder_handle: &Handle_Geom_CylindricalSurface,
        ) -> UniquePtr<Handle_Geom_Surface>;
        pub fn conical_to_surface(
            conical_handle: &Handle_Geom_ConicalSurface,
        ) -> UniquePtr<Handle_Geom_Surface>;
        pub fn bspline_to_surface(
            bspline_handle: &Handle_Geom_BSplineSurface,
        ) -> UniquePtr<Handle_Geom_Surface>;
        pub fn spherical_to_surface(
            spherical_handle: &Handle_Geom_SphericalSurface,
        ) -> UniquePtr<Handle_Geom_Surface>;
        pub fn toroidal_to_surface(
            toroidal_handle: &Handle_Geom_ToroidalSurface,
        ) -> UniquePtr<Handle_Geom_Surface>;

        type Geom_BezierSurface;
        pub fn Geom_BezierSurface_new(
            poles: &TColgp_Array2OfPnt,
        ) -> UniquePtr<Handle_Geom_BezierSurface>;
        pub fn bezier_to_surface(
            bezier_handle: &Handle_Geom_BezierSurface,
        ) -> UniquePtr<Handle_Geom_Surface>;

        type Geom_BezierCurve;
        #[cxx_name = "construct_unique"]
        pub fn Geom_BezierCurve_new_points(
            poles: &TColgp_HArray1OfPnt,
        ) -> UniquePtr<Geom_BezierCurve>;

        pub fn Geom_BezierCurve_to_handle(
            law: UniquePtr<Geom_BezierCurve>,
        ) -> UniquePtr<Handle_Geom_BezierCurve>;

        pub fn handle_geom_plane_location(plane: &Handle_Geom_Plane) -> &gp_Pnt;

        pub fn Handle_Geom_Plane_Pln(plane: &Handle_Geom_Plane) -> UniquePtr<gp_Pln>;

        pub fn new_HandleGeomPlane_from_HandleGeomSurface(
            geom_surface_handle: &Handle_Geom_Surface,
        ) -> UniquePtr<Handle_Geom_Plane>;

        #[cxx_name = "construct_unique"]
        pub fn new_HandleGeomCurve_from_HandleGeom_BSplineCurve(
            bspline_curve_handle: &Handle_Geom_BSplineCurve,
        ) -> UniquePtr<Handle_Geom_Curve>;

        #[cxx_name = "construct_unique"]
        pub fn new_HandleGeomCurve_from_HandleGeom_BezierCurve(
            bezier_curve_handle: &Handle_Geom_BezierCurve,
        ) -> UniquePtr<Handle_Geom_Curve>;

        #[cxx_name = "construct_unique"]
        pub fn new_HandleGeomCurve_from_HandleGeom_TrimmedCurve(
            trimmed_curve_handle: &Handle_Geom_TrimmedCurve,
        ) -> UniquePtr<Handle_Geom_Curve>;

        #[cxx_name = "construct_unique"]
        pub fn new_HandleGeomCurve_from_HandleGeom_Circle(
            circle_handle: &Handle_Geom_Circle,
        ) -> UniquePtr<Handle_Geom_Curve>;

        #[cxx_name = "construct_unique"]
        pub fn new_HandleGeomCurve_from_HandleGeom_Ellipse(
            ellipse_handle: &Handle_Geom_Ellipse,
        ) -> UniquePtr<Handle_Geom_Curve>;

        #[cxx_name = "construct_unique"]
        pub fn new_HandleGeomCurve_from_HandleGeom_Hyperbola(
            hyperbola_handle: &Handle_Geom_Hyperbola,
        ) -> UniquePtr<Handle_Geom_Curve>;

        #[cxx_name = "construct_unique"]
        pub fn new_HandleGeomCurve_from_HandleGeom_Parabola(
            parabola_handle: &Handle_Geom_Parabola,
        ) -> UniquePtr<Handle_Geom_Curve>;

        #[cxx_name = "construct_unique"]
        pub fn new_HandleGeomCurve_from_HandleGeom_OffsetCurve(
            offset_curve_handle: &Handle_Geom_OffsetCurve,
        ) -> UniquePtr<Handle_Geom_Curve>;

        // Curve construction
        pub fn Geom_Line_new(point: &gp_Pnt, direction: &gp_Dir) -> UniquePtr<Handle_Geom_Line>;
        pub fn Geom_Circle_new(axis: &gp_Ax2, radius: f64) -> UniquePtr<Handle_Geom_Circle>;
        pub fn Geom_Ellipse_new(
            axis: &gp_Ax2,
            major_radius: f64,
            minor_radius: f64,
        ) -> Result<UniquePtr<Handle_Geom_Ellipse>>;
        pub fn Geom_Hyperbola_new(
            axis: &gp_Ax2,
            major_radius: f64,
            minor_radius: f64,
        ) -> Result<UniquePtr<Handle_Geom_Hyperbola>>;
        pub fn Geom_Parabola_new(axis: &gp_Ax2, focal: f64) -> Result<UniquePtr<Handle_Geom_Parabola>>;
        pub fn Geom_TrimmedCurve_new(
            curve: &Handle_Geom_Curve,
            u1: f64,
            u2: f64,
        ) -> Result<UniquePtr<Handle_Geom_TrimmedCurve>>;
        pub fn Geom_OffsetCurve_new(
            curve: &Handle_Geom_Curve,
            offset: f64,
            direction: &gp_Dir,
        ) -> Result<UniquePtr<Handle_Geom_OffsetCurve>>;
        pub fn Geom_BezierCurve_new(
            poles: &TColgp_Array1OfPnt,
        ) -> Result<UniquePtr<Handle_Geom_BezierCurve>>;
        pub fn Geom_BezierCurve_new_rational(
            poles: &TColgp_Array1OfPnt,
            weights: &TColStd_Array1OfReal,
        ) -> Result<UniquePtr<Handle_Geom_BezierCurve>>;
        pub fn Geom_BSplineCurve_new(
            poles: &TColgp_Array1OfPnt,
            knots: &TColStd_Array1OfReal,
            multiplicities: &TColStd_Array1OfInteger,
            degree: i32,
        ) -> Result<UniquePtr<Handle_Geom_BSplineCurve>>;
        #[allow(clippy::too_many_arguments)]
        pub fn Geom_BSplineCurve_new_full(
            poles: &TColgp_Array1OfPnt,
            weights: &TColStd_Array1OfReal,
            knots: &TColStd_Array1OfReal,
            multiplicities: &TColStd_Array1OfInteger,
            degree: i32,
            periodic: bool,
            check_rational: bool,
        ) -> Result<UniquePtr<Handle_Geom_BSplineCurve>>;

        // Curve accessors
        pub fn Geom_Line_Lin(line: &Handle_Geom_Line) -> UniquePtr<gp_Lin>;
        pub fn Geom_Circle_Circ(circle: &Handle_Geom_Circle) -> UniquePtr<gp_Circ>;
        pub fn Geom_Ellipse_Elips(ellipse: &Handle_Geom_Ellipse) -> UniquePtr<gp_Elips>;
        pub fn Geom_Hyperbola_Hypr(hyperbola: &Handle_Geom_Hyperbola) -> UniquePtr<gp_Hypr>;
        pub fn Geom_Parabola_Parab(parabola: &Handle_Geom_Parabola) -> UniquePtr<gp_Parab>;
        pub fn Geom_OffsetCurve_Direction(curve: &Handle_Geom_OffsetCurve) -> &gp_Dir;
        pub fn Geom_OffsetCurve_Offset(curve: &Handle_Geom_OffsetCurve) -> f64;
        pub fn Geom_OffsetCurve_BasisCurve(
            curve: &Handle_Geom_OffsetCurve,
        ) -> UniquePtr<Handle_Geom_Curve>;
        pub fn Geom_TrimmedCurve_BasisCurve(
            curve: &Handle_Geom_TrimmedCurve,
        ) -> UniquePtr<Handle_Geom_Curve>;

        // B-spline curve accessors
        pub fn HandleGeomBSplineCurve_Degree(curve: &Handle_Geom_BSplineCurve) -> i32;
        pub fn HandleGeomBSplineCurve_MaxDegree() -> i32;
        pub fn HandleGeomBSplineCurve_NbPoles(curve: &Handle_Geom_BSplineCurve) -> i32;
        pub fn HandleGeomBSplineCurve_NbKnots(curve: &Handle_Geom_BSplineCurve) -> i32;
        pub fn HandleGeomBSplineCurve_IsPeriodic(curve: &Handle_Geom_BSplineCurve) -> bool;
        pub fn HandleGeomBSplineCurve_IsRational(curve: &Handle_Geom_BSplineCurve) -> bool;
        pub fn HandleGeomBSplineCurve_StartPoint(
            curve: &Handle_Geom_BSplineCurve,
        ) -> UniquePtr<gp_Pnt>;
        pub fn HandleGeomBSplineCurve_EndPoint(
            curve: &Handle_Geom_BSplineCurve,
        ) -> UniquePtr<gp_Pnt>;
        pub fn HandleGeomBSplineCurve_FirstUKnotIndex(curve: &Handle_Geom_BSplineCurve) -> i32;
        pub fn HandleGeomBSplineCurve_LastUKnotIndex(curve: &Handle_Geom_BSplineCurve) -> i32;
        pub fn HandleGeomBSplineCurve_Continuity(curve: &Handle_Geom_BSplineCurve) -> GeomAbs_Shape;
        pub fn HandleGeomBSplineCurve_Knot(curve: &Handle_Geom_BSplineCurve, index: i32) -> f64;
        pub fn HandleGeomBSplineCurve_Multiplicity(
            curve: &Handle_Geom_BSplineCurve,
            index: i32,
        ) -> i32;
        pub fn HandleGeomBSplineCurve_Pole(
            curve: &Handle_Geom_BSplineCurve,
            index: i32,
        ) -> UniquePtr<gp_Pnt>;
        pub fn HandleGeomBSplineCurve_Weight(curve: &Handle_Geom_BSplineCurve, index: i32) -> f64;
        pub fn HandleGeomBSplineCurve_Value(
            curve: &Handle_Geom_BSplineCurve,
            u: f64,
        ) -> UniquePtr<gp_Pnt>;
        pub fn HandleGeomBSplineCurve_Resolution(
            curve: &Handle_Geom_BSplineCurve,
            tolerance3d: f64,
        ) -> f64;
        pub fn HandleGeomBSplineCurve_SetPeriodic(
            curve: Pin<&mut Handle_Geom_BSplineCurve>,
        ) -> Result<()>;
        pub fn HandleGeomBSplineCurve_SetNotPeriodic(curve: Pin<&mut Handle_Geom_BSplineCurve>);
        pub fn HandleGeomBSplineCurve_Segment(
            curve: Pin<&mut Handle_Geom_BSplineCurve>,
            u1: f64,
            u2: f64,
        ) -> Result<()>;
        pub fn HandleGeomBSplineCurve_RemoveKnot(
            curve: Pin<&mut Handle_Geom_BSplineCurve>,
            index: i32,
            m: i32,
            tolerance: f64,
        ) -> Result<bool>;
        pub fn HandleGeomBSplineCurve_InsertKnot(
            curve: Pin<&mut Handle_Geom_BSplineCurve>,
            u: f64,
            m: i32,
            tolerance: f64,
        );
        pub fn HandleGeomBSplineCurve_SetKnots(
            curve: Pin<&mut Handle_Geom_BSplineCurve>,
            knots: &TColStd_Array1OfReal,
        ) -> Result<()>;
        /// The expanded knot sequence (`Geom_BSplineCurve::KnotSequence`).
        pub fn HandleGeomBSplineCurve_KnotSequence(
            curve: &Handle_Geom_BSplineCurve,
        ) -> UniquePtr<TColStd_Array1OfReal>;
        /// A copy of the curve, for re-segmentation without mutating the shared
        /// curve an edge stores.
        pub fn HandleGeomBSplineCurve_Copy(
            curve: &Handle_Geom_BSplineCurve,
        ) -> UniquePtr<Handle_Geom_BSplineCurve>;

        // Bezier curve accessors
        pub fn HandleGeomBezierCurve_NbPoles(curve: &Handle_Geom_BezierCurve) -> i32;
        pub fn HandleGeomBezierCurve_Pole(
            curve: &Handle_Geom_BezierCurve,
            index: i32,
        ) -> UniquePtr<gp_Pnt>;
        pub fn HandleGeomBezierCurve_Weight(curve: &Handle_Geom_BezierCurve, index: i32) -> f64;

        // Dynamic dispatch
        pub fn GeomCurve_IsKind_line(curve: &Handle_Geom_Curve) -> bool;
        pub fn GeomCurve_IsKind_circle(curve: &Handle_Geom_Curve) -> bool;
        pub fn GeomCurve_IsKind_ellipse(curve: &Handle_Geom_Curve) -> bool;
        pub fn GeomCurve_IsKind_hyperbola(curve: &Handle_Geom_Curve) -> bool;
        pub fn GeomCurve_IsKind_parabola(curve: &Handle_Geom_Curve) -> bool;
        pub fn GeomCurve_IsKind_bezier(curve: &Handle_Geom_Curve) -> bool;
        pub fn GeomCurve_IsKind_bspline(curve: &Handle_Geom_Curve) -> bool;
        pub fn GeomCurve_IsKind_offset(curve: &Handle_Geom_Curve) -> bool;
        pub fn GeomCurve_IsKind_trimmed(curve: &Handle_Geom_Curve) -> bool;
        pub fn GeomCurve_DownCast_line(curve: &Handle_Geom_Curve) -> UniquePtr<Handle_Geom_Line>;
        pub fn GeomCurve_DownCast_circle(curve: &Handle_Geom_Curve) -> UniquePtr<Handle_Geom_Circle>;
        pub fn GeomCurve_DownCast_ellipse(curve: &Handle_Geom_Curve) -> UniquePtr<Handle_Geom_Ellipse>;
        pub fn GeomCurve_DownCast_hyperbola(curve: &Handle_Geom_Curve) -> UniquePtr<Handle_Geom_Hyperbola>;
        pub fn GeomCurve_DownCast_parabola(curve: &Handle_Geom_Curve) -> UniquePtr<Handle_Geom_Parabola>;
        pub fn GeomCurve_DownCast_bezier(curve: &Handle_Geom_Curve) -> UniquePtr<Handle_Geom_BezierCurve>;
        pub fn GeomCurve_DownCast_bspline(curve: &Handle_Geom_Curve) -> UniquePtr<Handle_Geom_BSplineCurve>;
        pub fn GeomCurve_DownCast_offset(curve: &Handle_Geom_Curve) -> UniquePtr<Handle_Geom_OffsetCurve>;
        pub fn GeomCurve_DownCast_trimmed(curve: &Handle_Geom_Curve) -> UniquePtr<Handle_Geom_TrimmedCurve>;

        // Surfaces
        pub fn Geom_ConicalSurface_new(
            axis: &gp_Ax3,
            angle: f64,
            radius: f64,
        ) -> Result<UniquePtr<Handle_Geom_ConicalSurface>>;
        pub fn Geom_SphericalSurface_new(
            axis: &gp_Ax3,
            radius: f64,
        ) -> Result<UniquePtr<Handle_Geom_SphericalSurface>>;
        pub fn Geom_ToroidalSurface_new(
            axis: &gp_Ax3,
            major_radius: f64,
            minor_radius: f64,
        ) -> Result<UniquePtr<Handle_Geom_ToroidalSurface>>;
        pub fn Geom_Surface_Bounds(
            surface: &Handle_Geom_Surface,
            u1: &mut f64,
            u2: &mut f64,
            v1: &mut f64,
            v2: &mut f64,
        );
        pub fn Geom_BSplineSurface_new(
            poles: &TColgp_Array2OfPnt,
            uknots: &TColStd_Array1OfReal,
            vknots: &TColStd_Array1OfReal,
            umults: &TColStd_Array1OfInteger,
            vmults: &TColStd_Array1OfInteger,
            udegree: i32,
            vdegree: i32,
        ) -> Result<UniquePtr<Handle_Geom_BSplineSurface>>;
        #[allow(clippy::too_many_arguments)]
        pub fn Geom_BSplineSurface_new_full(
            poles: &TColgp_Array2OfPnt,
            weights: &TColStd_Array2OfReal,
            uknots: &TColStd_Array1OfReal,
            vknots: &TColStd_Array1OfReal,
            umults: &TColStd_Array1OfInteger,
            vmults: &TColStd_Array1OfInteger,
            udegree: i32,
            vdegree: i32,
            uperiodic: bool,
            vperiodic: bool,
        ) -> Result<UniquePtr<Handle_Geom_BSplineSurface>>;

        // B-spline surface readers
        pub fn HandleGeomBSplineSurface_Value(
            surface: &Handle_Geom_BSplineSurface,
            u: f64,
            v: f64,
        ) -> UniquePtr<gp_Pnt>;
        pub fn HandleGeomBSplineSurface_Pole(
            surface: &Handle_Geom_BSplineSurface,
            u_index: i32,
            v_index: i32,
        ) -> UniquePtr<gp_Pnt>;
        pub fn HandleGeomBSplineSurface_Weight(
            surface: &Handle_Geom_BSplineSurface,
            u_index: i32,
            v_index: i32,
        ) -> f64;
        pub fn HandleGeomBSplineSurface_UDegree(surface: &Handle_Geom_BSplineSurface) -> i32;
        pub fn HandleGeomBSplineSurface_VDegree(surface: &Handle_Geom_BSplineSurface) -> i32;
        pub fn HandleGeomBSplineSurface_NbUPoles(surface: &Handle_Geom_BSplineSurface) -> i32;
        pub fn HandleGeomBSplineSurface_NbVPoles(surface: &Handle_Geom_BSplineSurface) -> i32;
        pub fn HandleGeomBSplineSurface_NbUKnots(surface: &Handle_Geom_BSplineSurface) -> i32;
        pub fn HandleGeomBSplineSurface_NbVKnots(surface: &Handle_Geom_BSplineSurface) -> i32;
        pub fn HandleGeomBSplineSurface_IsUPeriodic(surface: &Handle_Geom_BSplineSurface) -> bool;
        pub fn HandleGeomBSplineSurface_IsVPeriodic(surface: &Handle_Geom_BSplineSurface) -> bool;
        pub fn HandleGeomBSplineSurface_UKnot(
            surface: &Handle_Geom_BSplineSurface,
            index: i32,
        ) -> f64;
        pub fn HandleGeomBSplineSurface_VKnot(
            surface: &Handle_Geom_BSplineSurface,
            index: i32,
        ) -> f64;
        pub fn HandleGeomBSplineSurface_UMultiplicity(
            surface: &Handle_Geom_BSplineSurface,
            index: i32,
        ) -> i32;
        pub fn HandleGeomBSplineSurface_VMultiplicity(
            surface: &Handle_Geom_BSplineSurface,
            index: i32,
        ) -> i32;
        pub fn HandleGeomBSplineSurface_Bounds(
            surface: &Handle_Geom_BSplineSurface,
            u1: &mut f64,
            u2: &mut f64,
            v1: &mut f64,
            v2: &mut f64,
        );
        pub fn HandleGeomBSplineSurface_UKnotSequence(
            surface: &Handle_Geom_BSplineSurface,
        ) -> &TColStd_Array1OfReal;
        pub fn HandleGeomBSplineSurface_VKnotSequence(
            surface: &Handle_Geom_BSplineSurface,
        ) -> &TColStd_Array1OfReal;
        pub fn downcast_to_bspline_surface(
            surface: &Handle_Geom_Surface,
        ) -> UniquePtr<Handle_Geom_BSplineSurface>;
    }

    impl UniquePtr<Handle_Geom_CylindricalSurface> {}
    impl UniquePtr<Handle_Geom_BezierSurface> {}
    impl UniquePtr<Handle_Geom_BezierCurve> {}
    impl UniquePtr<Handle_Geom_Plane> {}
    impl UniquePtr<Handle_Geom_BSplineCurve> {}
    impl UniquePtr<Handle_Geom_TrimmedCurve> {}
    impl UniquePtr<Handle_Geom_Surface> {}
    impl UniquePtr<Handle_Geom_Curve> {}
    impl UniquePtr<Handle_Geom_Line> {}
    impl UniquePtr<Handle_Geom_Circle> {}
    impl UniquePtr<Handle_Geom_Ellipse> {}
    impl UniquePtr<Handle_Geom_Hyperbola> {}
    impl UniquePtr<Handle_Geom_Parabola> {}
    impl UniquePtr<Handle_Geom_OffsetCurve> {}
    impl UniquePtr<Handle_Geom_ConicalSurface> {}
    impl UniquePtr<Handle_Geom_SphericalSurface> {}
    impl UniquePtr<Handle_Geom_ToroidalSurface> {}
    impl UniquePtr<Handle_Geom_BSplineSurface> {}
}
