// Binary Operation Algorithms
pub use inner::*;

#[cxx::bridge]
mod inner {
    #[derive(Debug)]
    #[repr(u32)]
    pub enum BOPAlgo_GlueEnum {
        BOPAlgo_GlueOff,
        BOPAlgo_GlueShift,
        BOPAlgo_GlueFull,
    }

    #[derive(Debug)]
    #[repr(u32)]
    pub enum BOPAlgo_Operation {
        BOPAlgo_COMMON,
        BOPAlgo_FUSE,
        BOPAlgo_CUT,
        BOPAlgo_CUT21,
        BOPAlgo_SECTION,
        BOPAlgo_UNKNOWN,
    }

    unsafe extern "C++" {
        include!("opencascade-sys/include/bop_algo.hxx");

        type BOPAlgo_GlueEnum;
        type BOPAlgo_Operation;

        type TopoDS_Face = crate::topo_ds::TopoDS_Face;
        type TopTools_ListOfShape = crate::top_tools::TopTools_ListOfShape;
        type TopAbs_Orientation = crate::top_abs::TopAbs_Orientation;

        type BOPAlgo_BuilderFace;
        #[cxx_name = "construct_unique"]
        pub fn BOPAlgo_BuilderFace_new() -> UniquePtr<BOPAlgo_BuilderFace>;
        pub fn SetFace(self: Pin<&mut BOPAlgo_BuilderFace>, face: &TopoDS_Face);
        pub fn Face(self: &BOPAlgo_BuilderFace) -> &TopoDS_Face;
        pub fn SetShapes(self: Pin<&mut BOPAlgo_BuilderFace>, shapes: &TopTools_ListOfShape);
        pub fn Areas(self: &BOPAlgo_BuilderFace) -> &TopTools_ListOfShape;
        pub fn Shapes(self: &BOPAlgo_BuilderFace) -> &TopTools_ListOfShape;
        pub fn BOPAlgo_BuilderFace_Perform(
            builder_face: Pin<&mut BOPAlgo_BuilderFace>,
        ) -> Result<()>;
        pub fn BOPAlgo_BuilderFace_SetAvoidInternalShapes(
            builder_face: Pin<&mut BOPAlgo_BuilderFace>,
            avoid: bool,
        );
        pub fn HasErrors(self: &BOPAlgo_BuilderFace) -> bool;
        pub fn Orientation(self: &BOPAlgo_BuilderFace) -> TopAbs_Orientation;
    }
}
