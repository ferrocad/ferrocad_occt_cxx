pub use inner::*;

#[cxx::bridge]
mod inner {
    unsafe extern "C++" {
        include!("opencascade-sys/include/b_rep_adaptor.hxx");

        type gp_Pnt = crate::gp::gp_Pnt;
        type gp_Vec = crate::gp::gp_Vec;
        type GeomAbs_CurveType = crate::geom_abs::GeomAbs_CurveType;
        type TopoDS_Edge = crate::topo_ds::TopoDS_Edge;
        type TopoDS_Face = crate::topo_ds::TopoDS_Face;

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

        type BRepAdaptor_Surface;
        #[cxx_name = "construct_unique"]
        pub fn BRepAdaptor_Surface_new(face: &TopoDS_Face) -> UniquePtr<BRepAdaptor_Surface>;
        pub fn BRepAdaptor_Surface_value(
            surface: &BRepAdaptor_Surface,
            u: f64,
            v: f64,
        ) -> UniquePtr<gp_Pnt>;
    }
}
