pub use inner::*;

#[cxx::bridge]
mod inner {
    unsafe extern "C++" {
        include!("opencascade-sys/include/b_rep_algo_api.hxx");

        type TopoDS_Shape = crate::topo_ds::TopoDS_Shape;
        type TopTools_ListOfShape = crate::top_tools::TopTools_ListOfShape;
        type Message_ProgressRange = crate::message::Message_ProgressRange;
        type BOPAlgo_GlueEnum = crate::bop_algo::BOPAlgo_GlueEnum;
        type BOPAlgo_Operation = crate::bop_algo::BOPAlgo_Operation;

        pub type BRepAlgoAPI_BuilderAlgo;
        pub fn SectionEdges(self: Pin<&mut BRepAlgoAPI_BuilderAlgo>) -> &TopTools_ListOfShape;

        pub type BRepAlgoAPI_Fuse;
        #[cxx_name = "construct_unique"]
        pub fn BRepAlgoAPI_Fuse_new(
            shape_1: &TopoDS_Shape,
            shape_2: &TopoDS_Shape,
        ) -> UniquePtr<BRepAlgoAPI_Fuse>;
        pub fn Shape(self: Pin<&mut BRepAlgoAPI_Fuse>) -> &TopoDS_Shape;
        pub fn Build(self: Pin<&mut BRepAlgoAPI_Fuse>, progress: &Message_ProgressRange);
        pub fn IsDone(self: &BRepAlgoAPI_Fuse) -> bool;
        pub fn SectionEdges(self: Pin<&mut BRepAlgoAPI_Fuse>) -> &TopTools_ListOfShape;
        pub fn SetGlue(self: Pin<&mut BRepAlgoAPI_Fuse>, glue: BOPAlgo_GlueEnum);
        pub fn Modified<'a>(
            self: Pin<&'a mut BRepAlgoAPI_Fuse>,
            shape: &'a TopoDS_Shape,
        ) -> &'a TopTools_ListOfShape;
        pub fn Generated<'a>(
            self: Pin<&'a mut BRepAlgoAPI_Fuse>,
            shape: &'a TopoDS_Shape,
        ) -> &'a TopTools_ListOfShape;
        pub fn IsDeleted(self: Pin<&mut BRepAlgoAPI_Fuse>, shape: &TopoDS_Shape) -> bool;

        type BRepAlgoAPI_Cut;
        #[cxx_name = "construct_unique"]
        pub fn BRepAlgoAPI_Cut_new(
            shape_1: &TopoDS_Shape,
            shape_2: &TopoDS_Shape,
        ) -> UniquePtr<BRepAlgoAPI_Cut>;
        #[cxx_name = "construct_unique"]
        pub fn BRepAlgoAPI_Cut_new_default() -> UniquePtr<BRepAlgoAPI_Cut>;
        pub fn Shape(self: Pin<&mut BRepAlgoAPI_Cut>) -> &TopoDS_Shape;
        pub fn Build(self: Pin<&mut BRepAlgoAPI_Cut>, progress: &Message_ProgressRange);
        pub fn IsDone(self: &BRepAlgoAPI_Cut) -> bool;
        pub fn Generated<'a>(
            self: Pin<&'a mut BRepAlgoAPI_Cut>,
            shape: &'a TopoDS_Shape,
        ) -> &'a TopTools_ListOfShape;
        pub fn Modified<'a>(
            self: Pin<&'a mut BRepAlgoAPI_Cut>,
            shape: &'a TopoDS_Shape,
        ) -> &'a TopTools_ListOfShape;
        pub fn IsDeleted(self: Pin<&mut BRepAlgoAPI_Cut>, shape: &TopoDS_Shape) -> bool;
        pub fn SectionEdges(self: Pin<&mut BRepAlgoAPI_Cut>) -> &TopTools_ListOfShape;
        pub fn SetOperation(self: Pin<&mut BRepAlgoAPI_Cut>, operation: BOPAlgo_Operation);
        pub fn SetArguments(self: Pin<&mut BRepAlgoAPI_Cut>, arguments: &TopTools_ListOfShape);
        pub fn SetTools(self: Pin<&mut BRepAlgoAPI_Cut>, tools: &TopTools_ListOfShape);
        pub fn SetNonDestructive(self: Pin<&mut BRepAlgoAPI_Cut>, enabled: bool);
        // `BOPAlgo_Options` is a protected base of `BRepAlgoAPI_Cut`, so a
        // direct method binding cannot form a pointer to the inherited member.
        pub fn BRepAlgoAPI_Cut_SetRunParallel(op: Pin<&mut BRepAlgoAPI_Cut>, enabled: bool);
        pub fn BRepAlgoAPI_Cut_SetFuzzyValue(op: Pin<&mut BRepAlgoAPI_Cut>, value: f64);
        pub fn Arguments(self: &BRepAlgoAPI_Cut) -> &TopTools_ListOfShape;
        pub fn Tools(self: &BRepAlgoAPI_Cut) -> &TopTools_ListOfShape;

        type BRepAlgoAPI_Common;
        #[cxx_name = "construct_unique"]
        pub fn BRepAlgoAPI_Common_new(
            shape_1: &TopoDS_Shape,
            shape_2: &TopoDS_Shape,
        ) -> UniquePtr<BRepAlgoAPI_Common>;
        pub fn Shape(self: Pin<&mut BRepAlgoAPI_Common>) -> &TopoDS_Shape;
        pub fn Build(self: Pin<&mut BRepAlgoAPI_Common>, progress: &Message_ProgressRange);
        pub fn IsDone(self: &BRepAlgoAPI_Common) -> bool;
        pub fn SectionEdges(self: Pin<&mut BRepAlgoAPI_Common>) -> &TopTools_ListOfShape;
        pub fn Modified<'a>(
            self: Pin<&'a mut BRepAlgoAPI_Common>,
            shape: &'a TopoDS_Shape,
        ) -> &'a TopTools_ListOfShape;
        pub fn Generated<'a>(
            self: Pin<&'a mut BRepAlgoAPI_Common>,
            shape: &'a TopoDS_Shape,
        ) -> &'a TopTools_ListOfShape;
        pub fn IsDeleted(self: Pin<&mut BRepAlgoAPI_Common>, shape: &TopoDS_Shape) -> bool;

        type BRepAlgoAPI_Section;
        #[cxx_name = "construct_unique"]
        pub fn BRepAlgoAPI_Section_new(
            shape_1: &TopoDS_Shape,
            shape_2: &TopoDS_Shape,
        ) -> UniquePtr<BRepAlgoAPI_Section>;
        pub fn Shape(self: Pin<&mut BRepAlgoAPI_Section>) -> &TopoDS_Shape;
        pub fn Build(self: Pin<&mut BRepAlgoAPI_Section>, progress: &Message_ProgressRange);
        pub fn IsDone(self: &BRepAlgoAPI_Section) -> bool;
        pub fn SectionEdges(self: Pin<&mut BRepAlgoAPI_Section>) -> &TopTools_ListOfShape;

        type BRepAlgoAPI_Defeaturing;
        pub fn BRepAlgoAPI_Defeaturing_new() -> UniquePtr<BRepAlgoAPI_Defeaturing>;
        pub fn BRepAlgoAPI_Defeaturing_SetRunParallel(
            defeaturing: Pin<&mut BRepAlgoAPI_Defeaturing>,
            enabled: bool,
        );
        pub fn BRepAlgoAPI_Defeaturing_SetToFillHistory(
            defeaturing: Pin<&mut BRepAlgoAPI_Defeaturing>,
            enabled: bool,
        );
        pub fn BRepAlgoAPI_Defeaturing_SetShape(
            defeaturing: Pin<&mut BRepAlgoAPI_Defeaturing>,
            shape: &TopoDS_Shape,
        );
        pub fn BRepAlgoAPI_Defeaturing_AddFaceToRemove(
            defeaturing: Pin<&mut BRepAlgoAPI_Defeaturing>,
            shape: &TopoDS_Shape,
        );
        pub fn BRepAlgoAPI_Defeaturing_Build(
            defeaturing: Pin<&mut BRepAlgoAPI_Defeaturing>,
        ) -> Result<()>;
        pub fn BRepAlgoAPI_Defeaturing_IsDone(
            defeaturing: &BRepAlgoAPI_Defeaturing,
        ) -> bool;
        pub fn BRepAlgoAPI_Defeaturing_Shape(
            defeaturing: Pin<&mut BRepAlgoAPI_Defeaturing>,
        ) -> UniquePtr<TopoDS_Shape>;
    }
}
