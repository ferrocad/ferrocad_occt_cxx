pub use inner::*;

#[cxx::bridge]
mod inner {
    unsafe extern "C++" {
        include!("opencascade-sys/include/b_rep_feat.hxx");

        type gp_Ax1 = crate::gp::gp_Ax1;
        type TopoDS_Shape = crate::topo_ds::TopoDS_Shape;
        type TopoDS_Face = crate::topo_ds::TopoDS_Face;
        type TopoDS_Edge = crate::topo_ds::TopoDS_Edge;
        type TopoDS_Wire = crate::topo_ds::TopoDS_Wire;
        type TopoDS_Compound = crate::topo_ds::TopoDS_Compound;
        type TopTools_ListOfShape = crate::top_tools::TopTools_ListOfShape;

        type BRepFeat_MakeDPrism;
        #[cxx_name = "construct_unique"]
        pub fn BRepFeat_MakeDPrism_new(
            shape: &TopoDS_Shape,
            profile_base: &TopoDS_Face,
            sketch_base: &TopoDS_Face,
            angle: f64,
            fuse: i32, // 0 = subtractive, 1 = additive
            modify: bool,
        ) -> UniquePtr<BRepFeat_MakeDPrism>;

        #[cxx_name = "Perform"]
        pub fn perform_until_face(self: Pin<&mut BRepFeat_MakeDPrism>, until: &TopoDS_Shape);
        #[cxx_name = "Perform"]
        pub fn perform_with_height(self: Pin<&mut BRepFeat_MakeDPrism>, height: f64);
        pub fn Shape(self: Pin<&mut BRepFeat_MakeDPrism>) -> &TopoDS_Shape;

        type BRepFeat_MakeCylindricalHole;
        #[cxx_name = "construct_unique"]
        pub fn BRepFeat_MakeCylindricalHole_new() -> UniquePtr<BRepFeat_MakeCylindricalHole>;
        pub fn Init(
            self: Pin<&mut BRepFeat_MakeCylindricalHole>,
            shape: &TopoDS_Shape,
            axis: &gp_Ax1,
        );
        pub fn Perform(self: Pin<&mut BRepFeat_MakeCylindricalHole>, radius: f64);
        pub fn Build(self: Pin<&mut BRepFeat_MakeCylindricalHole>);
        pub fn Shape(self: &BRepFeat_MakeCylindricalHole) -> &TopoDS_Shape;

        type BRepFeat_SplitShape;
        #[cxx_name = "construct_unique"]
        pub fn BRepFeat_SplitShape_new() -> UniquePtr<BRepFeat_SplitShape>;
        #[cxx_name = "construct_unique"]
        pub fn BRepFeat_SplitShape_new_from_shape(
            shape: &TopoDS_Shape,
        ) -> UniquePtr<BRepFeat_SplitShape>;
        pub fn BRepFeat_SplitShape_Add_wire_face(
            split: Pin<&mut BRepFeat_SplitShape>,
            wire: &TopoDS_Wire,
            face: &TopoDS_Face,
        ) -> Result<()>;
        pub fn BRepFeat_SplitShape_Add_edge_face(
            split: Pin<&mut BRepFeat_SplitShape>,
            edge: &TopoDS_Edge,
            face: &TopoDS_Face,
        ) -> Result<()>;
        pub fn BRepFeat_SplitShape_Add_compound_face(
            split: Pin<&mut BRepFeat_SplitShape>,
            compound: &TopoDS_Compound,
            face: &TopoDS_Face,
        ) -> Result<()>;
        pub fn BRepFeat_SplitShape_Add_edge_edge(
            split: Pin<&mut BRepFeat_SplitShape>,
            edge: &TopoDS_Edge,
            edge_on: &TopoDS_Edge,
        ) -> Result<()>;
        pub fn BRepFeat_SplitShape_Build(
            split: Pin<&mut BRepFeat_SplitShape>,
        ) -> Result<()>;
        pub fn BRepFeat_SplitShape_DirectLeft(
            split: Pin<&mut BRepFeat_SplitShape>,
        ) -> &TopTools_ListOfShape;
        pub fn BRepFeat_SplitShape_Left(
            split: Pin<&mut BRepFeat_SplitShape>,
        ) -> &TopTools_ListOfShape;
        pub fn IsDone(self: &BRepFeat_SplitShape) -> bool;
        pub fn Shape(self: Pin<&mut BRepFeat_SplitShape>) -> &TopoDS_Shape;
        pub fn Modified(
            self: Pin<&mut BRepFeat_SplitShape>,
            shape: &TopoDS_Shape,
        ) -> &TopTools_ListOfShape;
    }
}
