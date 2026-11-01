pub use inner::*;

#[cxx::bridge]
mod inner {
    unsafe extern "C++" {
        include!("opencascade-sys/include/b_rep_tools.hxx");

        type TopoDS_Shape = crate::topo_ds::TopoDS_Shape;
        type TopoDS_Face = crate::topo_ds::TopoDS_Face;
        type TopoDS_Wire = crate::topo_ds::TopoDS_Wire;
        type TopoDS_Edge = crate::topo_ds::TopoDS_Edge;
        type TopAbs_ShapeEnum = crate::top_abs::TopAbs_ShapeEnum;
        type TopAbs_Orientation = crate::top_abs::TopAbs_Orientation;

        type BRepTools;
        #[Self = "BRepTools"]
        pub fn UVBounds(
            face: &TopoDS_Face,
            u0: &mut f64,
            u1: &mut f64,
            v0: &mut f64,
            v1: &mut f64,
        );

        fn outer_wire(face: &TopoDS_Face) -> UniquePtr<TopoDS_Wire>;

        #[cxx_name = "write_brep_text"]
        pub fn write(shape: &TopoDS_Shape, path: String) -> bool;
        #[cxx_name = "read_brep_text"]
        pub fn read(path: String) -> UniquePtr<TopoDS_Shape>;

        pub fn write_brep_bytes(shape: &TopoDS_Shape, out: &mut Vec<u8>);
        pub fn read_brep_bytes(data: &[u8]) -> UniquePtr<TopoDS_Shape>;

        type BRepTools_ReShape;
        #[cxx_name = "construct_unique"]
        pub fn BRepTools_ReShape_new() -> UniquePtr<BRepTools_ReShape>;
        pub fn Clear(self: Pin<&mut BRepTools_ReShape>);
        pub fn Remove(self: Pin<&mut BRepTools_ReShape>, shape: &TopoDS_Shape);
        pub fn Replace(
            self: Pin<&mut BRepTools_ReShape>,
            shape: &TopoDS_Shape,
            new_shape: &TopoDS_Shape,
        );
        pub fn IsRecorded(self: &BRepTools_ReShape, shape: &TopoDS_Shape) -> bool;
        pub fn BRepTools_ReShape_Value(
            reshape: &BRepTools_ReShape,
            shape: &TopoDS_Shape,
        ) -> UniquePtr<TopoDS_Shape>;
        pub fn BRepTools_ReShape_Status(
            reshape: Pin<&mut BRepTools_ReShape>,
            shape: &TopoDS_Shape,
            new_shape: Pin<&mut TopoDS_Shape>,
            last: bool,
        ) -> i32;
        pub fn BRepTools_ReShape_Apply(
            reshape: Pin<&mut BRepTools_ReShape>,
            shape: &TopoDS_Shape,
            until: TopAbs_ShapeEnum,
        ) -> UniquePtr<TopoDS_Shape>;

        type BRepTools_WireExplorer;
        #[cxx_name = "construct_unique"]
        pub fn BRepTools_WireExplorer_new(
            wire: &TopoDS_Wire,
        ) -> UniquePtr<BRepTools_WireExplorer>;
        pub fn More(self: &BRepTools_WireExplorer) -> bool;
        pub fn Next(self: Pin<&mut BRepTools_WireExplorer>);
        pub fn Current(self: &BRepTools_WireExplorer) -> &TopoDS_Edge;
        pub fn Orientation(self: &BRepTools_WireExplorer) -> TopAbs_Orientation;
    }
}
