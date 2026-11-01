pub use inner::*;

#[cxx::bridge]
mod inner {
    unsafe extern "C++" {
        include!("opencascade-sys/include/b_rep_fill.hxx");

        type TopoDS_Edge = crate::topo_ds::TopoDS_Edge;
        type TopoDS_Face = crate::topo_ds::TopoDS_Face;
        type GeomAbs_Shape = crate::geom_api::GeomAbs_Shape;

        pub fn BRepFill_Face(
            edge1: &TopoDS_Edge,
            edge2: &TopoDS_Edge,
        ) -> Result<UniquePtr<TopoDS_Face>>;

        type BRepFill_Filling;
        #[cxx_name = "construct_unique"]
        pub fn BRepFill_Filling_new() -> UniquePtr<BRepFill_Filling>;
        pub fn Add(
            self: Pin<&mut BRepFill_Filling>,
            edge: &TopoDS_Edge,
            order: GeomAbs_Shape,
            is_boundary: bool,
        ) -> i32;
        pub fn IsDone(self: &BRepFill_Filling) -> bool;
        pub fn BRepFill_Filling_Build(filling: Pin<&mut BRepFill_Filling>) -> Result<()>;
        pub fn BRepFill_Filling_Face(filling: &BRepFill_Filling) -> UniquePtr<TopoDS_Face>;
    }
}
