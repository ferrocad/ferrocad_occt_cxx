pub use inner::*;

#[cxx::bridge]
mod inner {
    unsafe extern "C++" {
        include!("opencascade-sys/include/b_rep_check.hxx");

        type TopoDS_Shape = crate::topo_ds::TopoDS_Shape;

        type BRepCheck_Analyzer;
        #[cxx_name = "construct_unique"]
        pub fn BRepCheck_Analyzer_new(
            shape: &TopoDS_Shape,
            geometry: bool,
        ) -> UniquePtr<BRepCheck_Analyzer>;
        pub fn Init(self: Pin<&mut BRepCheck_Analyzer>, shape: &TopoDS_Shape, geometry: bool);
        pub fn IsValid(self: &BRepCheck_Analyzer) -> bool;
    }
}
