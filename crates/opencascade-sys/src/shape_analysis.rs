pub use inner::*;

#[cxx::bridge]
mod inner {
    unsafe extern "C++" {
        include!("opencascade-sys/include/shape_analysis.hxx");

        type TopoDS_Shape = crate::topo_ds::TopoDS_Shape;
        type TopAbs_ShapeEnum = crate::top_abs::TopAbs_ShapeEnum;
        type Handle_TopTools_HSequenceOfShape = crate::top_tools::Handle_TopTools_HSequenceOfShape;

        pub fn ShapeAnalysis_FreeBounds_ConnectEdgesToWires(
            edges: Pin<&mut Handle_TopTools_HSequenceOfShape>,
            tolerance: f64,
            shared: bool,
            wires: Pin<&mut Handle_TopTools_HSequenceOfShape>,
        );

        type ShapeAnalysis_ShapeTolerance;
        #[cxx_name = "construct_unique"]
        pub fn ShapeAnalysis_ShapeTolerance_new() -> UniquePtr<ShapeAnalysis_ShapeTolerance>;
        pub fn ShapeAnalysis_ShapeTolerance_Tolerance(
            analysis: Pin<&mut ShapeAnalysis_ShapeTolerance>,
            shape: &TopoDS_Shape,
            mode: i32,
            shape_type: TopAbs_ShapeEnum,
        );
        pub fn ShapeAnalysis_ShapeTolerance_GlobalTolerance(
            analysis: &ShapeAnalysis_ShapeTolerance,
            mode: i32,
        ) -> f64;
        pub fn ShapeAnalysis_ShapeTolerance_OverTolerance(
            analysis: &ShapeAnalysis_ShapeTolerance,
            shape: &TopoDS_Shape,
            value: f64,
            shape_type: TopAbs_ShapeEnum,
        ) -> UniquePtr<Handle_TopTools_HSequenceOfShape>;
        pub fn ShapeAnalysis_ShapeTolerance_InTolerance(
            analysis: &ShapeAnalysis_ShapeTolerance,
            shape: &TopoDS_Shape,
            valmin: f64,
            valmax: f64,
            shape_type: TopAbs_ShapeEnum,
        ) -> UniquePtr<Handle_TopTools_HSequenceOfShape>;
    }
}
