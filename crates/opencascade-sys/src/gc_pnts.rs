pub use inner::*;

#[cxx::bridge]
mod inner {
    unsafe extern "C++" {
        include!("opencascade-sys/include/gc_pnts.hxx");

        type gp_Pnt = crate::gp::gp_Pnt;
        type BRepAdaptor_Curve = crate::b_rep_adaptor::BRepAdaptor_Curve;

        type GCPnts_TangentialDeflection;
        #[cxx_name = "construct_unique"]
        fn TangentialDeflection_new(
            curve: &BRepAdaptor_Curve,
            angular_deflection: f64,
            curvature_deflection: f64,
        ) -> UniquePtr<GCPnts_TangentialDeflection>;
        fn GCPnts_TangentialDeflection_new_range(
            curve: &BRepAdaptor_Curve,
            first: f64,
            last: f64,
            angular_deflection: f64,
            curvature_deflection: f64,
            min_points: i32,
        ) -> Result<UniquePtr<GCPnts_TangentialDeflection>>;
        fn NbPoints(self: &GCPnts_TangentialDeflection) -> i32;
        fn GCPnts_TangentialDeflection_Value(
            approximator: &GCPnts_TangentialDeflection,
            index: i32,
        ) -> UniquePtr<gp_Pnt>;

        type GCPnts_UniformAbscissa;
        #[cxx_name = "construct_unique"]
        fn GCPnts_UniformAbscissa_new() -> UniquePtr<GCPnts_UniformAbscissa>;
        fn GCPnts_UniformAbscissa_Initialize_abscissa(
            algorithm: Pin<&mut GCPnts_UniformAbscissa>,
            curve: &BRepAdaptor_Curve,
            abscissa: f64,
        ) -> Result<()>;
        fn GCPnts_UniformAbscissa_Initialize_number(
            algorithm: Pin<&mut GCPnts_UniformAbscissa>,
            curve: &BRepAdaptor_Curve,
            number: i32,
            first: f64,
            last: f64,
        ) -> Result<()>;
        fn IsDone(self: &GCPnts_UniformAbscissa) -> bool;
        fn GCPnts_UniformAbscissa_NbPoints(algorithm: &GCPnts_UniformAbscissa) -> Result<i32>;
        fn GCPnts_UniformAbscissa_Parameter(
            algorithm: &GCPnts_UniformAbscissa,
            index: i32,
        ) -> Result<f64>;

        type GCPnts_UniformDeflection;
        fn GCPnts_UniformDeflection_new(
            curve: &BRepAdaptor_Curve,
            deflection: f64,
            first: f64,
            last: f64,
        ) -> Result<UniquePtr<GCPnts_UniformDeflection>>;
        fn IsDone(self: &GCPnts_UniformDeflection) -> bool;
        fn GCPnts_UniformDeflection_NbPoints(algorithm: &GCPnts_UniformDeflection) -> Result<i32>;
        fn GCPnts_UniformDeflection_Value(
            algorithm: &GCPnts_UniformDeflection,
            index: i32,
        ) -> Result<UniquePtr<gp_Pnt>>;

        type GCPnts_AbscissaPoint;
        fn GCPnts_AbscissaPoint_Length(curve: &BRepAdaptor_Curve, tol: f64) -> Result<f64>;
        fn GCPnts_AbscissaPoint_new(
            tol: f64,
            curve: &BRepAdaptor_Curve,
            abscissa: f64,
            first: f64,
        ) -> Result<UniquePtr<GCPnts_AbscissaPoint>>;
        fn IsDone(self: &GCPnts_AbscissaPoint) -> bool;
        fn GCPnts_AbscissaPoint_Parameter(algorithm: &GCPnts_AbscissaPoint) -> Result<f64>;
    }
}
