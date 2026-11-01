pub use inner::*;

#[cxx::bridge]
mod inner {
    unsafe extern "C++" {
        include!("opencascade-sys/include/shape_fix.hxx");

        type TopoDS_Shape = crate::topo_ds::TopoDS_Shape;
        type TopoDS_Edge = crate::topo_ds::TopoDS_Edge;
        type TopoDS_Face = crate::topo_ds::TopoDS_Face;
        type TopoDS_Shell = crate::topo_ds::TopoDS_Shell;
        type TopoDS_Solid = crate::topo_ds::TopoDS_Solid;
        type TopoDS_Wire = crate::topo_ds::TopoDS_Wire;
        type TopoDS_Vertex = crate::topo_ds::TopoDS_Vertex;
        type TopoDS_Compound = crate::topo_ds::TopoDS_Compound;
        type Handle_Geom_Surface = crate::geom::Handle_Geom_Surface;
        type TopLoc_Location = crate::top_loc::TopLoc_Location;

        type Handle_ShapeFix_Root;
        type Handle_ShapeFix_Edge;
        type Handle_ShapeFix_Wire;
        type Handle_ShapeFix_Face;
        type Handle_ShapeFix_Shell;
        type Handle_ShapeFix_Solid;
        type Handle_ShapeFix_Shape;

        // Construction
        pub fn ShapeFix_Root_new() -> UniquePtr<Handle_ShapeFix_Root>;
        pub fn ShapeFix_Edge_new() -> UniquePtr<Handle_ShapeFix_Edge>;
        pub fn ShapeFix_Wire_new() -> UniquePtr<Handle_ShapeFix_Wire>;
        pub fn ShapeFix_Wire_from_wire(
            wire: &TopoDS_Wire,
            face: &TopoDS_Face,
            prec: f64,
        ) -> Result<UniquePtr<Handle_ShapeFix_Wire>>;
        pub fn ShapeFix_Face_new() -> UniquePtr<Handle_ShapeFix_Face>;
        pub fn ShapeFix_Face_from_face(face: &TopoDS_Face) -> Result<UniquePtr<Handle_ShapeFix_Face>>;
        pub fn ShapeFix_Shell_new() -> UniquePtr<Handle_ShapeFix_Shell>;
        pub fn ShapeFix_Shell_from_shell(
            shell: &TopoDS_Shell,
        ) -> Result<UniquePtr<Handle_ShapeFix_Shell>>;
        pub fn ShapeFix_Solid_new() -> UniquePtr<Handle_ShapeFix_Solid>;
        pub fn ShapeFix_Solid_from_solid(
            solid: &TopoDS_Solid,
        ) -> Result<UniquePtr<Handle_ShapeFix_Solid>>;
        pub fn ShapeFix_Shape_new() -> UniquePtr<Handle_ShapeFix_Shape>;
        pub fn ShapeFix_Shape_from_shape(
            shape: &TopoDS_Shape,
        ) -> Result<UniquePtr<Handle_ShapeFix_Shape>>;

        // ShapeFix_Root
        pub fn ShapeFix_Root_set_precision(h: &Handle_ShapeFix_Root, value: f64);
        pub fn ShapeFix_Root_precision(h: &Handle_ShapeFix_Root) -> f64;
        pub fn ShapeFix_Root_set_min_tolerance(h: &Handle_ShapeFix_Root, value: f64);
        pub fn ShapeFix_Root_min_tolerance(h: &Handle_ShapeFix_Root) -> f64;
        pub fn ShapeFix_Root_set_max_tolerance(h: &Handle_ShapeFix_Root, value: f64);
        pub fn ShapeFix_Root_max_tolerance(h: &Handle_ShapeFix_Root) -> f64;
        pub fn ShapeFix_Root_limit_tolerance(h: &Handle_ShapeFix_Root, value: f64) -> f64;

        pub fn ShapeFix_Wire_as_root(h: &Handle_ShapeFix_Wire) -> &Handle_ShapeFix_Root;
        pub fn ShapeFix_Face_as_root(h: &Handle_ShapeFix_Face) -> &Handle_ShapeFix_Root;
        pub fn ShapeFix_Shell_as_root(h: &Handle_ShapeFix_Shell) -> &Handle_ShapeFix_Root;
        pub fn ShapeFix_Solid_as_root(h: &Handle_ShapeFix_Solid) -> &Handle_ShapeFix_Root;
        pub fn ShapeFix_Shape_as_root(h: &Handle_ShapeFix_Shape) -> &Handle_ShapeFix_Root;

        // ShapeFix_Edge
        pub fn ShapeFix_Edge_FixRemovePCurve_face(
            h: &Handle_ShapeFix_Edge,
            edge: &TopoDS_Edge,
            face: &TopoDS_Face,
        ) -> Result<bool>;
        pub fn ShapeFix_Edge_FixRemovePCurve_surface(
            h: &Handle_ShapeFix_Edge,
            edge: &TopoDS_Edge,
            surface: &Handle_Geom_Surface,
            location: &TopLoc_Location,
        ) -> Result<bool>;
        pub fn ShapeFix_Edge_FixRemoveCurve3d(
            h: &Handle_ShapeFix_Edge,
            edge: &TopoDS_Edge,
        ) -> Result<bool>;
        pub fn ShapeFix_Edge_FixAddPCurve_face(
            h: &Handle_ShapeFix_Edge,
            edge: &TopoDS_Edge,
            face: &TopoDS_Face,
            seam: bool,
            prec: f64,
        ) -> Result<bool>;
        pub fn ShapeFix_Edge_FixAddPCurve_surface(
            h: &Handle_ShapeFix_Edge,
            edge: &TopoDS_Edge,
            surface: &Handle_Geom_Surface,
            location: &TopLoc_Location,
            seam: bool,
            prec: f64,
        ) -> Result<bool>;
        pub fn ShapeFix_Edge_FixAddCurve3d(
            h: &Handle_ShapeFix_Edge,
            edge: &TopoDS_Edge,
        ) -> Result<bool>;
        pub fn ShapeFix_Edge_FixVertexTolerance_face(
            h: &Handle_ShapeFix_Edge,
            edge: &TopoDS_Edge,
            face: &TopoDS_Face,
        ) -> Result<bool>;
        pub fn ShapeFix_Edge_FixVertexTolerance(
            h: &Handle_ShapeFix_Edge,
            edge: &TopoDS_Edge,
        ) -> Result<bool>;
        pub fn ShapeFix_Edge_FixReversed2d_face(
            h: &Handle_ShapeFix_Edge,
            edge: &TopoDS_Edge,
            face: &TopoDS_Face,
        ) -> Result<bool>;
        pub fn ShapeFix_Edge_FixReversed2d_surface(
            h: &Handle_ShapeFix_Edge,
            edge: &TopoDS_Edge,
            surface: &Handle_Geom_Surface,
            location: &TopLoc_Location,
        ) -> Result<bool>;
        pub fn ShapeFix_Edge_FixSameParameter(
            h: &Handle_ShapeFix_Edge,
            edge: &TopoDS_Edge,
            tolerance: f64,
        ) -> Result<bool>;
        pub fn ShapeFix_Edge_FixSameParameter_face(
            h: &Handle_ShapeFix_Edge,
            edge: &TopoDS_Edge,
            face: &TopoDS_Face,
            tolerance: f64,
        ) -> Result<bool>;

        // ShapeFix_Wire — action methods
        pub fn ShapeFix_Wire_Init(
            h: &Handle_ShapeFix_Wire,
            wire: &TopoDS_Wire,
            face: &TopoDS_Face,
            prec: f64,
        ) -> Result<()>;
        pub fn ShapeFix_Wire_Load(h: &Handle_ShapeFix_Wire, wire: &TopoDS_Wire) -> Result<()>;
        pub fn ShapeFix_Wire_SetFace(h: &Handle_ShapeFix_Wire, face: &TopoDS_Face) -> Result<()>;
        pub fn ShapeFix_Wire_SetSurface(
            h: &Handle_ShapeFix_Wire,
            surface: &Handle_Geom_Surface,
        ) -> Result<()>;
        pub fn ShapeFix_Wire_SetSurface_placed(
            h: &Handle_ShapeFix_Wire,
            surface: &Handle_Geom_Surface,
            location: &TopLoc_Location,
        ) -> Result<()>;
        pub fn ShapeFix_Wire_SetMaxTailAngle(h: &Handle_ShapeFix_Wire, value: f64);
        pub fn ShapeFix_Wire_SetMaxTailWidth(h: &Handle_ShapeFix_Wire, value: f64);
        pub fn ShapeFix_Wire_IsLoaded(h: &Handle_ShapeFix_Wire) -> bool;
        pub fn ShapeFix_Wire_IsReady(h: &Handle_ShapeFix_Wire) -> bool;
        pub fn ShapeFix_Wire_NbEdges(h: &Handle_ShapeFix_Wire) -> i32;
        pub fn ShapeFix_Wire_Wire(h: &Handle_ShapeFix_Wire) -> Result<UniquePtr<TopoDS_Wire>>;
        pub fn ShapeFix_Wire_WireAPIMake(h: &Handle_ShapeFix_Wire) -> Result<UniquePtr<TopoDS_Wire>>;
        pub fn ShapeFix_Wire_Face(h: &Handle_ShapeFix_Wire) -> Result<UniquePtr<TopoDS_Face>>;
        pub fn ShapeFix_Wire_Perform(h: &Handle_ShapeFix_Wire) -> Result<bool>;
        pub fn ShapeFix_Wire_ClearModes(h: &Handle_ShapeFix_Wire);
        pub fn ShapeFix_Wire_ClearStatuses(h: &Handle_ShapeFix_Wire);
        pub fn ShapeFix_Wire_FixEdgeTool(h: &Handle_ShapeFix_Wire) -> UniquePtr<Handle_ShapeFix_Edge>;
        pub fn ShapeFix_Wire_FixReorder(h: &Handle_ShapeFix_Wire) -> Result<bool>;
        pub fn ShapeFix_Wire_FixSmall_global(
            h: &Handle_ShapeFix_Wire,
            lock: bool,
            prec: f64,
        ) -> Result<i32>;
        pub fn ShapeFix_Wire_FixSmall_one(
            h: &Handle_ShapeFix_Wire,
            num: i32,
            lock: bool,
            prec: f64,
        ) -> Result<bool>;
        pub fn ShapeFix_Wire_FixConnected(h: &Handle_ShapeFix_Wire, prec: f64) -> Result<bool>;
        pub fn ShapeFix_Wire_FixConnected_one(
            h: &Handle_ShapeFix_Wire,
            num: i32,
            prec: f64,
        ) -> Result<bool>;
        pub fn ShapeFix_Wire_FixEdgeCurves(h: &Handle_ShapeFix_Wire) -> Result<bool>;
        pub fn ShapeFix_Wire_FixDegenerated(h: &Handle_ShapeFix_Wire) -> Result<bool>;
        pub fn ShapeFix_Wire_FixDegenerated_one(
            h: &Handle_ShapeFix_Wire,
            num: i32,
        ) -> Result<bool>;
        pub fn ShapeFix_Wire_FixSelfIntersection(h: &Handle_ShapeFix_Wire) -> Result<bool>;
        pub fn ShapeFix_Wire_FixLacking(h: &Handle_ShapeFix_Wire, force: bool) -> Result<bool>;
        pub fn ShapeFix_Wire_FixLacking_one(
            h: &Handle_ShapeFix_Wire,
            num: i32,
            force: bool,
        ) -> Result<bool>;
        pub fn ShapeFix_Wire_FixClosed(h: &Handle_ShapeFix_Wire, prec: f64) -> Result<bool>;
        pub fn ShapeFix_Wire_FixGaps3d(h: &Handle_ShapeFix_Wire) -> Result<bool>;
        pub fn ShapeFix_Wire_FixGaps2d(h: &Handle_ShapeFix_Wire) -> Result<bool>;
        pub fn ShapeFix_Wire_FixSeam(h: &Handle_ShapeFix_Wire, num: i32) -> Result<bool>;
        pub fn ShapeFix_Wire_FixShifted(h: &Handle_ShapeFix_Wire) -> Result<bool>;
        pub fn ShapeFix_Wire_FixNotchedEdges(h: &Handle_ShapeFix_Wire) -> Result<bool>;
        pub fn ShapeFix_Wire_FixGap3d(
            h: &Handle_ShapeFix_Wire,
            num: i32,
            convert: bool,
        ) -> Result<bool>;
        pub fn ShapeFix_Wire_FixGap2d(
            h: &Handle_ShapeFix_Wire,
            num: i32,
            convert: bool,
        ) -> Result<bool>;
        pub fn ShapeFix_Wire_FixTails(h: &Handle_ShapeFix_Wire) -> Result<bool>;

        // ShapeFix_Wire — modes
        pub fn ShapeFix_Wire_ModifyTopologyMode(h: &Handle_ShapeFix_Wire) -> bool;
        pub fn ShapeFix_Wire_set_ModifyTopologyMode(h: &Handle_ShapeFix_Wire, value: bool);
        pub fn ShapeFix_Wire_ModifyGeometryMode(h: &Handle_ShapeFix_Wire) -> bool;
        pub fn ShapeFix_Wire_set_ModifyGeometryMode(h: &Handle_ShapeFix_Wire, value: bool);
        pub fn ShapeFix_Wire_ClosedWireMode(h: &Handle_ShapeFix_Wire) -> bool;
        pub fn ShapeFix_Wire_set_ClosedWireMode(h: &Handle_ShapeFix_Wire, value: bool);
        pub fn ShapeFix_Wire_PreferencePCurveMode(h: &Handle_ShapeFix_Wire) -> bool;
        pub fn ShapeFix_Wire_set_PreferencePCurveMode(h: &Handle_ShapeFix_Wire, value: bool);
        pub fn ShapeFix_Wire_FixGapsByRangesMode(h: &Handle_ShapeFix_Wire) -> bool;
        pub fn ShapeFix_Wire_set_FixGapsByRangesMode(h: &Handle_ShapeFix_Wire, value: bool);
        pub fn ShapeFix_Wire_ModifyRemoveLoopMode(h: &Handle_ShapeFix_Wire) -> i32;
        pub fn ShapeFix_Wire_set_ModifyRemoveLoopMode(h: &Handle_ShapeFix_Wire, value: i32);
        pub fn ShapeFix_Wire_FixReorderMode(h: &Handle_ShapeFix_Wire) -> i32;
        pub fn ShapeFix_Wire_set_FixReorderMode(h: &Handle_ShapeFix_Wire, value: i32);
        pub fn ShapeFix_Wire_FixSmallMode(h: &Handle_ShapeFix_Wire) -> i32;
        pub fn ShapeFix_Wire_set_FixSmallMode(h: &Handle_ShapeFix_Wire, value: i32);
        pub fn ShapeFix_Wire_FixConnectedMode(h: &Handle_ShapeFix_Wire) -> i32;
        pub fn ShapeFix_Wire_set_FixConnectedMode(h: &Handle_ShapeFix_Wire, value: i32);
        pub fn ShapeFix_Wire_FixEdgeCurvesMode(h: &Handle_ShapeFix_Wire) -> i32;
        pub fn ShapeFix_Wire_set_FixEdgeCurvesMode(h: &Handle_ShapeFix_Wire, value: i32);
        pub fn ShapeFix_Wire_FixDegeneratedMode(h: &Handle_ShapeFix_Wire) -> i32;
        pub fn ShapeFix_Wire_set_FixDegeneratedMode(h: &Handle_ShapeFix_Wire, value: i32);
        pub fn ShapeFix_Wire_FixSelfIntersectionMode(h: &Handle_ShapeFix_Wire) -> i32;
        pub fn ShapeFix_Wire_set_FixSelfIntersectionMode(h: &Handle_ShapeFix_Wire, value: i32);
        pub fn ShapeFix_Wire_FixLackingMode(h: &Handle_ShapeFix_Wire) -> i32;
        pub fn ShapeFix_Wire_set_FixLackingMode(h: &Handle_ShapeFix_Wire, value: i32);
        pub fn ShapeFix_Wire_FixGaps3dMode(h: &Handle_ShapeFix_Wire) -> i32;
        pub fn ShapeFix_Wire_set_FixGaps3dMode(h: &Handle_ShapeFix_Wire, value: i32);
        pub fn ShapeFix_Wire_FixGaps2dMode(h: &Handle_ShapeFix_Wire) -> i32;
        pub fn ShapeFix_Wire_set_FixGaps2dMode(h: &Handle_ShapeFix_Wire, value: i32);
        pub fn ShapeFix_Wire_FixReversed2dMode(h: &Handle_ShapeFix_Wire) -> i32;
        pub fn ShapeFix_Wire_set_FixReversed2dMode(h: &Handle_ShapeFix_Wire, value: i32);
        pub fn ShapeFix_Wire_FixRemovePCurveMode(h: &Handle_ShapeFix_Wire) -> i32;
        pub fn ShapeFix_Wire_set_FixRemovePCurveMode(h: &Handle_ShapeFix_Wire, value: i32);
        pub fn ShapeFix_Wire_FixAddPCurveMode(h: &Handle_ShapeFix_Wire) -> i32;
        pub fn ShapeFix_Wire_set_FixAddPCurveMode(h: &Handle_ShapeFix_Wire, value: i32);
        pub fn ShapeFix_Wire_FixRemoveCurve3dMode(h: &Handle_ShapeFix_Wire) -> i32;
        pub fn ShapeFix_Wire_set_FixRemoveCurve3dMode(h: &Handle_ShapeFix_Wire, value: i32);
        pub fn ShapeFix_Wire_FixAddCurve3dMode(h: &Handle_ShapeFix_Wire) -> i32;
        pub fn ShapeFix_Wire_set_FixAddCurve3dMode(h: &Handle_ShapeFix_Wire, value: i32);
        pub fn ShapeFix_Wire_FixSeamMode(h: &Handle_ShapeFix_Wire) -> i32;
        pub fn ShapeFix_Wire_set_FixSeamMode(h: &Handle_ShapeFix_Wire, value: i32);
        pub fn ShapeFix_Wire_FixShiftedMode(h: &Handle_ShapeFix_Wire) -> i32;
        pub fn ShapeFix_Wire_set_FixShiftedMode(h: &Handle_ShapeFix_Wire, value: i32);
        pub fn ShapeFix_Wire_FixSameParameterMode(h: &Handle_ShapeFix_Wire) -> i32;
        pub fn ShapeFix_Wire_set_FixSameParameterMode(h: &Handle_ShapeFix_Wire, value: i32);
        pub fn ShapeFix_Wire_FixVertexToleranceMode(h: &Handle_ShapeFix_Wire) -> i32;
        pub fn ShapeFix_Wire_set_FixVertexToleranceMode(h: &Handle_ShapeFix_Wire, value: i32);
        pub fn ShapeFix_Wire_FixNotchedEdgesMode(h: &Handle_ShapeFix_Wire) -> i32;
        pub fn ShapeFix_Wire_set_FixNotchedEdgesMode(h: &Handle_ShapeFix_Wire, value: i32);
        pub fn ShapeFix_Wire_FixSelfIntersectingEdgeMode(h: &Handle_ShapeFix_Wire) -> i32;
        pub fn ShapeFix_Wire_set_FixSelfIntersectingEdgeMode(h: &Handle_ShapeFix_Wire, value: i32);
        pub fn ShapeFix_Wire_FixIntersectingEdgesMode(h: &Handle_ShapeFix_Wire) -> i32;
        pub fn ShapeFix_Wire_set_FixIntersectingEdgesMode(h: &Handle_ShapeFix_Wire, value: i32);
        pub fn ShapeFix_Wire_FixNonAdjacentIntersectingEdgesMode(h: &Handle_ShapeFix_Wire) -> i32;
        pub fn ShapeFix_Wire_set_FixNonAdjacentIntersectingEdgesMode(
            h: &Handle_ShapeFix_Wire,
            value: i32,
        );
        pub fn ShapeFix_Wire_FixTailMode(h: &Handle_ShapeFix_Wire) -> i32;
        pub fn ShapeFix_Wire_set_FixTailMode(h: &Handle_ShapeFix_Wire, value: i32);

        // ShapeFix_Face
        pub fn ShapeFix_Face_Init(h: &Handle_ShapeFix_Face, face: &TopoDS_Face) -> Result<()>;
        pub fn ShapeFix_Face_Init_surface(
            h: &Handle_ShapeFix_Face,
            surface: &Handle_Geom_Surface,
            prec: f64,
            fwd: bool,
        ) -> Result<()>;
        pub fn ShapeFix_Face_Add(h: &Handle_ShapeFix_Face, wire: &TopoDS_Wire) -> Result<()>;
        pub fn ShapeFix_Face_Perform(h: &Handle_ShapeFix_Face) -> Result<bool>;
        pub fn ShapeFix_Face_FixOrientation(h: &Handle_ShapeFix_Face) -> Result<bool>;
        pub fn ShapeFix_Face_FixAddNaturalBound(h: &Handle_ShapeFix_Face) -> Result<bool>;
        pub fn ShapeFix_Face_FixMissingSeam(h: &Handle_ShapeFix_Face) -> Result<bool>;
        pub fn ShapeFix_Face_FixSmallAreaWire(
            h: &Handle_ShapeFix_Face,
            remove_small_face: bool,
        ) -> Result<bool>;
        pub fn ShapeFix_Face_FixIntersectingWires(h: &Handle_ShapeFix_Face) -> Result<bool>;
        pub fn ShapeFix_Face_FixWiresTwoCoincEdges(h: &Handle_ShapeFix_Face) -> Result<bool>;
        pub fn ShapeFix_Face_FixPeriodicDegenerated(h: &Handle_ShapeFix_Face) -> Result<bool>;
        pub fn ShapeFix_Face_Face(h: &Handle_ShapeFix_Face) -> Result<UniquePtr<TopoDS_Face>>;
        pub fn ShapeFix_Face_Result(h: &Handle_ShapeFix_Face) -> Result<UniquePtr<TopoDS_Shape>>;
        pub fn ShapeFix_Face_FixWireTool(h: &Handle_ShapeFix_Face) -> UniquePtr<Handle_ShapeFix_Wire>;
        pub fn ShapeFix_Face_ClearModes(h: &Handle_ShapeFix_Face);
        pub fn ShapeFix_Face_FixWireMode(h: &Handle_ShapeFix_Face) -> i32;
        pub fn ShapeFix_Face_set_FixWireMode(h: &Handle_ShapeFix_Face, value: i32);
        pub fn ShapeFix_Face_FixOrientationMode(h: &Handle_ShapeFix_Face) -> i32;
        pub fn ShapeFix_Face_set_FixOrientationMode(h: &Handle_ShapeFix_Face, value: i32);
        pub fn ShapeFix_Face_FixAddNaturalBoundMode(h: &Handle_ShapeFix_Face) -> i32;
        pub fn ShapeFix_Face_set_FixAddNaturalBoundMode(h: &Handle_ShapeFix_Face, value: i32);
        pub fn ShapeFix_Face_FixMissingSeamMode(h: &Handle_ShapeFix_Face) -> i32;
        pub fn ShapeFix_Face_set_FixMissingSeamMode(h: &Handle_ShapeFix_Face, value: i32);
        pub fn ShapeFix_Face_FixSmallAreaWireMode(h: &Handle_ShapeFix_Face) -> i32;
        pub fn ShapeFix_Face_set_FixSmallAreaWireMode(h: &Handle_ShapeFix_Face, value: i32);
        pub fn ShapeFix_Face_RemoveSmallAreaFaceMode(h: &Handle_ShapeFix_Face) -> i32;
        pub fn ShapeFix_Face_set_RemoveSmallAreaFaceMode(h: &Handle_ShapeFix_Face, value: i32);
        pub fn ShapeFix_Face_FixIntersectingWiresMode(h: &Handle_ShapeFix_Face) -> i32;
        pub fn ShapeFix_Face_set_FixIntersectingWiresMode(h: &Handle_ShapeFix_Face, value: i32);
        pub fn ShapeFix_Face_FixLoopWiresMode(h: &Handle_ShapeFix_Face) -> i32;
        pub fn ShapeFix_Face_set_FixLoopWiresMode(h: &Handle_ShapeFix_Face, value: i32);
        pub fn ShapeFix_Face_FixSplitFaceMode(h: &Handle_ShapeFix_Face) -> i32;
        pub fn ShapeFix_Face_set_FixSplitFaceMode(h: &Handle_ShapeFix_Face, value: i32);
        pub fn ShapeFix_Face_AutoCorrectPrecisionMode(h: &Handle_ShapeFix_Face) -> i32;
        pub fn ShapeFix_Face_set_AutoCorrectPrecisionMode(h: &Handle_ShapeFix_Face, value: i32);
        pub fn ShapeFix_Face_FixPeriodicDegeneratedMode(h: &Handle_ShapeFix_Face) -> i32;
        pub fn ShapeFix_Face_set_FixPeriodicDegeneratedMode(h: &Handle_ShapeFix_Face, value: i32);

        // ShapeFix_Shell
        pub fn ShapeFix_Shell_Init(h: &Handle_ShapeFix_Shell, shell: &TopoDS_Shell) -> Result<()>;
        pub fn ShapeFix_Shell_Perform(h: &Handle_ShapeFix_Shell) -> Result<bool>;
        pub fn ShapeFix_Shell_Shell(h: &Handle_ShapeFix_Shell) -> Result<UniquePtr<TopoDS_Shell>>;
        pub fn ShapeFix_Shell_Shape(h: &Handle_ShapeFix_Shell) -> Result<UniquePtr<TopoDS_Shape>>;
        pub fn ShapeFix_Shell_ErrorFaces(h: &Handle_ShapeFix_Shell)
            -> Result<UniquePtr<TopoDS_Compound>>;
        pub fn ShapeFix_Shell_NbShells(h: &Handle_ShapeFix_Shell) -> i32;
        pub fn ShapeFix_Shell_FixFaceTool(h: &Handle_ShapeFix_Shell)
            -> UniquePtr<Handle_ShapeFix_Face>;
        pub fn ShapeFix_Shell_FixFaceOrientation(
            h: &Handle_ShapeFix_Shell,
            shell: &TopoDS_Shell,
            multi_conex: bool,
            non_manifold: bool,
        ) -> Result<bool>;
        pub fn ShapeFix_Shell_SetNonManifoldFlag(h: &Handle_ShapeFix_Shell, value: bool);
        pub fn ShapeFix_Shell_FixFaceMode(h: &Handle_ShapeFix_Shell) -> i32;
        pub fn ShapeFix_Shell_set_FixFaceMode(h: &Handle_ShapeFix_Shell, value: i32);
        pub fn ShapeFix_Shell_FixOrientationMode(h: &Handle_ShapeFix_Shell) -> i32;
        pub fn ShapeFix_Shell_set_FixOrientationMode(h: &Handle_ShapeFix_Shell, value: i32);

        // ShapeFix_Solid
        pub fn ShapeFix_Solid_Init(h: &Handle_ShapeFix_Solid, solid: &TopoDS_Solid) -> Result<()>;
        pub fn ShapeFix_Solid_Perform(h: &Handle_ShapeFix_Solid) -> Result<bool>;
        pub fn ShapeFix_Solid_SolidFromShell(
            h: &Handle_ShapeFix_Solid,
            shell: &TopoDS_Shell,
        ) -> Result<UniquePtr<TopoDS_Solid>>;
        pub fn ShapeFix_Solid_Solid(h: &Handle_ShapeFix_Solid) -> Result<UniquePtr<TopoDS_Shape>>;
        pub fn ShapeFix_Solid_Shape(h: &Handle_ShapeFix_Solid) -> Result<UniquePtr<TopoDS_Shape>>;
        pub fn ShapeFix_Solid_FixShellTool(h: &Handle_ShapeFix_Solid)
            -> UniquePtr<Handle_ShapeFix_Shell>;
        pub fn ShapeFix_Solid_FixShellMode(h: &Handle_ShapeFix_Solid) -> i32;
        pub fn ShapeFix_Solid_set_FixShellMode(h: &Handle_ShapeFix_Solid, value: i32);
        pub fn ShapeFix_Solid_FixShellOrientationMode(h: &Handle_ShapeFix_Solid) -> i32;
        pub fn ShapeFix_Solid_set_FixShellOrientationMode(h: &Handle_ShapeFix_Solid, value: i32);
        pub fn ShapeFix_Solid_CreateOpenSolidMode(h: &Handle_ShapeFix_Solid) -> bool;
        pub fn ShapeFix_Solid_set_CreateOpenSolidMode(h: &Handle_ShapeFix_Solid, value: bool);

        // ShapeFix_Shape
        pub fn ShapeFix_Shape_Init(h: &Handle_ShapeFix_Shape, shape: &TopoDS_Shape) -> Result<()>;
        pub fn ShapeFix_Shape_Perform(h: &Handle_ShapeFix_Shape) -> Result<bool>;
        pub fn ShapeFix_Shape_Shape(h: &Handle_ShapeFix_Shape) -> Result<UniquePtr<TopoDS_Shape>>;
        pub fn ShapeFix_Shape_FixSolidTool(h: &Handle_ShapeFix_Shape)
            -> UniquePtr<Handle_ShapeFix_Solid>;
        pub fn ShapeFix_Shape_FixShellTool(h: &Handle_ShapeFix_Shape)
            -> UniquePtr<Handle_ShapeFix_Shell>;
        pub fn ShapeFix_Shape_FixFaceTool(h: &Handle_ShapeFix_Shape) -> UniquePtr<Handle_ShapeFix_Face>;
        pub fn ShapeFix_Shape_FixWireTool(h: &Handle_ShapeFix_Shape) -> UniquePtr<Handle_ShapeFix_Wire>;
        pub fn ShapeFix_Shape_FixEdgeTool(h: &Handle_ShapeFix_Shape) -> UniquePtr<Handle_ShapeFix_Edge>;
        pub fn ShapeFix_Shape_FixSolidMode(h: &Handle_ShapeFix_Shape) -> i32;
        pub fn ShapeFix_Shape_set_FixSolidMode(h: &Handle_ShapeFix_Shape, value: i32);
        pub fn ShapeFix_Shape_FixFreeShellMode(h: &Handle_ShapeFix_Shape) -> i32;
        pub fn ShapeFix_Shape_set_FixFreeShellMode(h: &Handle_ShapeFix_Shape, value: i32);
        pub fn ShapeFix_Shape_FixFreeFaceMode(h: &Handle_ShapeFix_Shape) -> i32;
        pub fn ShapeFix_Shape_set_FixFreeFaceMode(h: &Handle_ShapeFix_Shape, value: i32);
        pub fn ShapeFix_Shape_FixFreeWireMode(h: &Handle_ShapeFix_Shape) -> i32;
        pub fn ShapeFix_Shape_set_FixFreeWireMode(h: &Handle_ShapeFix_Shape, value: i32);
        pub fn ShapeFix_Shape_FixSameParameterMode(h: &Handle_ShapeFix_Shape) -> i32;
        pub fn ShapeFix_Shape_set_FixSameParameterMode(h: &Handle_ShapeFix_Shape, value: i32);
        pub fn ShapeFix_Shape_FixVertexPositionMode(h: &Handle_ShapeFix_Shape) -> i32;
        pub fn ShapeFix_Shape_set_FixVertexPositionMode(h: &Handle_ShapeFix_Shape, value: i32);
        pub fn ShapeFix_Shape_FixVertexTolMode(h: &Handle_ShapeFix_Shape) -> i32;
        pub fn ShapeFix_Shape_set_FixVertexTolMode(h: &Handle_ShapeFix_Shape, value: i32);
    }

    impl UniquePtr<Handle_ShapeFix_Root> {}
    impl UniquePtr<Handle_ShapeFix_Edge> {}
    impl UniquePtr<Handle_ShapeFix_Wire> {}
    impl UniquePtr<Handle_ShapeFix_Face> {}
    impl UniquePtr<Handle_ShapeFix_Shell> {}
    impl UniquePtr<Handle_ShapeFix_Solid> {}
    impl UniquePtr<Handle_ShapeFix_Shape> {}
}
