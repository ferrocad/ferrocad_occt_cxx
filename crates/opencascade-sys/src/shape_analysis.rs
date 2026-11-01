pub use inner::*;

#[cxx::bridge]
mod inner {
    unsafe extern "C++" {
        include!("opencascade-sys/include/shape_analysis.hxx");

        type TopoDS_Shape = crate::topo_ds::TopoDS_Shape;
        type TopoDS_Compound = crate::topo_ds::TopoDS_Compound;
        type TopoDS_Wire = crate::topo_ds::TopoDS_Wire;
        type TopAbs_ShapeEnum = crate::top_abs::TopAbs_ShapeEnum;
        type Handle_TopTools_HSequenceOfShape = crate::top_tools::Handle_TopTools_HSequenceOfShape;
        type Handle_Geom_Surface = crate::geom::Handle_Geom_Surface;
        type gp_Pnt = crate::gp::gp_Pnt;
        type gp_Pnt2d = crate::gp::gp_Pnt2d;

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

        type ShapeAnalysis_Shell;
        #[cxx_name = "construct_unique"]
        pub fn ShapeAnalysis_Shell_new() -> UniquePtr<ShapeAnalysis_Shell>;
        pub fn ShapeAnalysis_Shell_LoadShells(
            analysis: Pin<&mut ShapeAnalysis_Shell>,
            shape: &TopoDS_Shape,
        );
        pub fn ShapeAnalysis_Shell_CheckOrientedShells(
            analysis: Pin<&mut ShapeAnalysis_Shell>,
            shape: &TopoDS_Shape,
        );
        pub fn ShapeAnalysis_Shell_FreeEdges(
            analysis: Pin<&mut ShapeAnalysis_Shell>,
        ) -> UniquePtr<TopoDS_Compound>;

        type ShapeAnalysis_Surface;
        pub fn ShapeAnalysis_Surface_new(
            surface: &Handle_Geom_Surface,
        ) -> Result<UniquePtr<ShapeAnalysis_Surface>>;
        pub fn ShapeAnalysis_Surface_ValueOfUV(
            analysis: Pin<&mut ShapeAnalysis_Surface>,
            point: &gp_Pnt,
            tolerance: f64,
        ) -> Result<UniquePtr<gp_Pnt2d>>;

        type ShapeAnalysis_FreeBoundsProperties;
        pub fn ShapeAnalysis_FreeBoundsProperties_new(
            shape: &TopoDS_Shape,
        ) -> Result<UniquePtr<ShapeAnalysis_FreeBoundsProperties>>;
        pub fn ShapeAnalysis_FreeBoundsProperties_Perform(
            analysis: Pin<&mut ShapeAnalysis_FreeBoundsProperties>,
        ) -> Result<()>;
        pub fn ShapeAnalysis_FreeBoundsProperties_NbClosedFreeBounds(
            analysis: &ShapeAnalysis_FreeBoundsProperties,
        ) -> i32;
        pub fn ShapeAnalysis_FreeBoundsProperties_ClosedFreeBound(
            analysis: &ShapeAnalysis_FreeBoundsProperties,
            index: i32,
        ) -> Result<UniquePtr<TopoDS_Wire>>;
    }
}
