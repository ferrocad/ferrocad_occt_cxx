pub use inner::*;

#[cxx::bridge]
mod inner {
    unsafe extern "C++" {
        include!("opencascade-sys/include/b_rep_tools.hxx");

        type TopoDS_Shape = crate::topo_ds::TopoDS_Shape;
        type TopoDS_Face = crate::topo_ds::TopoDS_Face;
        type TopoDS_Wire = crate::topo_ds::TopoDS_Wire;

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
    }
}
