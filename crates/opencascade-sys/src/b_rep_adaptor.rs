pub use inner::*;

#[cxx::bridge]
mod inner {
    unsafe extern "C++" {
        include!("opencascade-sys/include/b_rep_adaptor.hxx");

        type gp_Pnt = crate::gp::gp_Pnt;
        type gp_Vec = crate::gp::gp_Vec;
        type gp_Pln = crate::gp::gp_Pln;
        type gp_Cylinder = crate::gp::gp_Cylinder;
        type gp_Sphere = crate::gp::gp_Sphere;
        type gp_Cone = crate::gp::gp_Cone;
        type gp_Torus = crate::gp::gp_Torus;
        type GeomAbs_CurveType = crate::geom_abs::GeomAbs_CurveType;
        type GeomAbs_SurfaceType = crate::geom_abs::GeomAbs_SurfaceType;
        type GeomAdaptor_Curve = crate::geom_adaptor::GeomAdaptor_Curve;
        type TopoDS_Edge = crate::topo_ds::TopoDS_Edge;
        type TopoDS_Face = crate::topo_ds::TopoDS_Face;
        type TopoDS_Wire = crate::topo_ds::TopoDS_Wire;

        type BRepAdaptor_Curve;
        #[cxx_name = "construct_unique"]
        pub fn BRepAdaptor_Curve_new(edge: &TopoDS_Edge) -> UniquePtr<BRepAdaptor_Curve>;
        pub fn FirstParameter(self: &BRepAdaptor_Curve) -> f64;
        pub fn LastParameter(self: &BRepAdaptor_Curve) -> f64;
        pub fn BRepAdaptor_Curve_value(curve: &BRepAdaptor_Curve, u: f64) -> UniquePtr<gp_Pnt>;
        pub fn BRepAdaptor_Curve_d1(
            curve: &BRepAdaptor_Curve,
            u: f64,
            point: Pin<&mut gp_Pnt>,
            vec: Pin<&mut gp_Vec>,
        );
        pub fn GetType(self: &BRepAdaptor_Curve) -> GeomAbs_CurveType;
        pub fn BRepAdaptor_Curve_Curve(curve: &BRepAdaptor_Curve) -> &GeomAdaptor_Curve;

        type BRepAdaptor_Surface;
        #[cxx_name = "construct_unique"]
        pub fn BRepAdaptor_Surface_new(face: &TopoDS_Face) -> UniquePtr<BRepAdaptor_Surface>;
        pub fn FirstUParameter(self: &BRepAdaptor_Surface) -> f64;
        pub fn LastUParameter(self: &BRepAdaptor_Surface) -> f64;
        pub fn FirstVParameter(self: &BRepAdaptor_Surface) -> f64;
        pub fn LastVParameter(self: &BRepAdaptor_Surface) -> f64;
        pub fn BRepAdaptor_Surface_GetType(
            surface: &BRepAdaptor_Surface,
        ) -> GeomAbs_SurfaceType;
        pub fn BRepAdaptor_Surface_Plane(
            surface: &BRepAdaptor_Surface,
        ) -> Result<UniquePtr<gp_Pln>>;
        pub fn BRepAdaptor_Surface_Cylinder(
            surface: &BRepAdaptor_Surface,
        ) -> Result<UniquePtr<gp_Cylinder>>;
        pub fn BRepAdaptor_Surface_Sphere(
            surface: &BRepAdaptor_Surface,
        ) -> Result<UniquePtr<gp_Sphere>>;
        pub fn BRepAdaptor_Surface_Cone(
            surface: &BRepAdaptor_Surface,
        ) -> Result<UniquePtr<gp_Cone>>;
        pub fn BRepAdaptor_Surface_Torus(
            surface: &BRepAdaptor_Surface,
        ) -> Result<UniquePtr<gp_Torus>>;
        pub fn BRepAdaptor_Surface_value(
            surface: &BRepAdaptor_Surface,
            u: f64,
            v: f64,
        ) -> UniquePtr<gp_Pnt>;

        type BRepAdaptor_CompCurve;
        #[cxx_name = "construct_unique"]
        pub fn BRepAdaptor_CompCurve_new(wire: &TopoDS_Wire) -> UniquePtr<BRepAdaptor_CompCurve>;
        pub fn FirstParameter(self: &BRepAdaptor_CompCurve) -> f64;
        pub fn LastParameter(self: &BRepAdaptor_CompCurve) -> f64;
        pub fn BRepAdaptor_CompCurve_value(
            curve: &BRepAdaptor_CompCurve,
            u: f64,
        ) -> UniquePtr<gp_Pnt>;
        pub fn BRepAdaptor_CompCurve_d1(
            curve: &BRepAdaptor_CompCurve,
            u: f64,
            point: Pin<&mut gp_Pnt>,
            vec: Pin<&mut gp_Vec>,
        );
    }
}
