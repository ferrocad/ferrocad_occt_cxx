#include <Standard_Failure.hxx>
#include <ShapeFix_Root.hxx>
#include <ShapeFix_Edge.hxx>
#include <ShapeFix_Wire.hxx>
#include <ShapeFix_Face.hxx>
#include <ShapeFix_Shell.hxx>
#include <ShapeFix_Solid.hxx>
#include <ShapeFix_Shape.hxx>
#include <ShapeFix_ShapeTolerance.hxx>
#include <Geom_Surface.hxx>
#include <TopAbs_ShapeEnum.hxx>
#include <TopLoc_Location.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Shell.hxx>
#include <TopoDS_Solid.hxx>
#include <TopoDS_Wire.hxx>
#include <TopoDS_Vertex.hxx>
#include <TopoDS_Compound.hxx>
#include <bindings_common.hxx>

#include <stdexcept>

// `Standard_Failure` is not derived from `std::exception` on OCCT 7.x, so a
// helper that lets an OCCT call throw must translate it into
// `std::runtime_error` (which cxx's `Result` shim understands) or the process
// aborts via `std::terminate`.
template <typename T> [[noreturn]] inline void rethrow_shapefix(const Standard_Failure &f) {
  const char *m = f.GetMessageString();
  throw std::runtime_error(m && *m ? m : "OCCT reported a failure");
}

#define SHAPEFIX_CATCH                                                                                \
  catch (const Standard_Failure &f) { rethrow_shapefix<void>(f); }                                    \
  catch (const std::exception &) { throw; }                                                           \
  catch (...) { throw std::runtime_error("unknown OCCT exception"); }

// ---------------------------------------------------------------------------
// Construction
// ---------------------------------------------------------------------------

inline std::unique_ptr<Handle_ShapeFix_Root> ShapeFix_Root_new() {
  return std::unique_ptr<Handle_ShapeFix_Root>(new Handle_ShapeFix_Root(new ShapeFix_Root()));
}

inline std::unique_ptr<Handle_ShapeFix_Edge> ShapeFix_Edge_new() {
  return std::unique_ptr<Handle_ShapeFix_Edge>(new Handle_ShapeFix_Edge(new ShapeFix_Edge()));
}

inline std::unique_ptr<Handle_ShapeFix_Wire> ShapeFix_Wire_new() {
  return std::unique_ptr<Handle_ShapeFix_Wire>(new Handle_ShapeFix_Wire(new ShapeFix_Wire()));
}

inline std::unique_ptr<Handle_ShapeFix_Wire> ShapeFix_Wire_from_wire(const TopoDS_Wire &wire,
                                                                     const TopoDS_Face &face,
                                                                     Standard_Real prec) {
  try {
    return std::unique_ptr<Handle_ShapeFix_Wire>(
        new Handle_ShapeFix_Wire(new ShapeFix_Wire(wire, face, prec)));
  }
  SHAPEFIX_CATCH
}

inline std::unique_ptr<Handle_ShapeFix_Face> ShapeFix_Face_new() {
  return std::unique_ptr<Handle_ShapeFix_Face>(new Handle_ShapeFix_Face(new ShapeFix_Face()));
}

inline std::unique_ptr<Handle_ShapeFix_Face> ShapeFix_Face_from_face(const TopoDS_Face &face) {
  try {
    return std::unique_ptr<Handle_ShapeFix_Face>(new Handle_ShapeFix_Face(new ShapeFix_Face(face)));
  }
  SHAPEFIX_CATCH
}

inline std::unique_ptr<Handle_ShapeFix_Shell> ShapeFix_Shell_new() {
  return std::unique_ptr<Handle_ShapeFix_Shell>(new Handle_ShapeFix_Shell(new ShapeFix_Shell()));
}

inline std::unique_ptr<Handle_ShapeFix_Shell> ShapeFix_Shell_from_shell(const TopoDS_Shell &shell) {
  try {
    return std::unique_ptr<Handle_ShapeFix_Shell>(
        new Handle_ShapeFix_Shell(new ShapeFix_Shell(shell)));
  }
  SHAPEFIX_CATCH
}

inline std::unique_ptr<Handle_ShapeFix_Solid> ShapeFix_Solid_new() {
  return std::unique_ptr<Handle_ShapeFix_Solid>(new Handle_ShapeFix_Solid(new ShapeFix_Solid()));
}

inline std::unique_ptr<Handle_ShapeFix_Solid> ShapeFix_Solid_from_solid(const TopoDS_Solid &solid) {
  try {
    return std::unique_ptr<Handle_ShapeFix_Solid>(
        new Handle_ShapeFix_Solid(new ShapeFix_Solid(solid)));
  }
  SHAPEFIX_CATCH
}

inline std::unique_ptr<Handle_ShapeFix_Shape> ShapeFix_Shape_new() {
  return std::unique_ptr<Handle_ShapeFix_Shape>(new Handle_ShapeFix_Shape(new ShapeFix_Shape()));
}

inline std::unique_ptr<Handle_ShapeFix_Shape> ShapeFix_Shape_from_shape(const TopoDS_Shape &shape) {
  try {
    return std::unique_ptr<Handle_ShapeFix_Shape>(
        new Handle_ShapeFix_Shape(new ShapeFix_Shape(shape)));
  }
  SHAPEFIX_CATCH
}

inline std::unique_ptr<ShapeFix_ShapeTolerance> ShapeFix_ShapeTolerance_new() {
  return std::unique_ptr<ShapeFix_ShapeTolerance>(new ShapeFix_ShapeTolerance());
}

inline void ShapeFix_ShapeTolerance_SetTolerance(const ShapeFix_ShapeTolerance &fix,
                                                 const TopoDS_Shape &shape, Standard_Real value,
                                                 TopAbs_ShapeEnum shape_type) {
  try {
    fix.SetTolerance(shape, value, shape_type);
  }
  SHAPEFIX_CATCH
}

inline Standard_Boolean ShapeFix_ShapeTolerance_LimitTolerance(const ShapeFix_ShapeTolerance &fix,
                                                               const TopoDS_Shape &shape,
                                                               Standard_Real minimum,
                                                               Standard_Real maximum,
                                                               TopAbs_ShapeEnum shape_type) {
  try {
    return fix.LimitTolerance(shape, minimum, maximum, shape_type);
  }
  SHAPEFIX_CATCH
}

// ---------------------------------------------------------------------------
// ShapeFix_Root (bound once, upcast from each derived handle)
// ---------------------------------------------------------------------------

inline void ShapeFix_Root_set_precision(const Handle_ShapeFix_Root &h, Standard_Real value) {
  h->SetPrecision(value);
}
inline Standard_Real ShapeFix_Root_precision(const Handle_ShapeFix_Root &h) { return h->Precision(); }
inline void ShapeFix_Root_set_min_tolerance(const Handle_ShapeFix_Root &h, Standard_Real value) {
  h->SetMinTolerance(value);
}
inline Standard_Real ShapeFix_Root_min_tolerance(const Handle_ShapeFix_Root &h) {
  return h->MinTolerance();
}
inline void ShapeFix_Root_set_max_tolerance(const Handle_ShapeFix_Root &h, Standard_Real value) {
  h->SetMaxTolerance(value);
}
inline Standard_Real ShapeFix_Root_max_tolerance(const Handle_ShapeFix_Root &h) {
  return h->MaxTolerance();
}
inline Standard_Real ShapeFix_Root_limit_tolerance(const Handle_ShapeFix_Root &h,
                                                   Standard_Real value) {
  return h->LimitTolerance(value);
}

inline const Handle_ShapeFix_Root &ShapeFix_Wire_as_root(const Handle_ShapeFix_Wire &h) { return h; }
inline const Handle_ShapeFix_Root &ShapeFix_Face_as_root(const Handle_ShapeFix_Face &h) { return h; }
inline const Handle_ShapeFix_Root &ShapeFix_Shell_as_root(const Handle_ShapeFix_Shell &h) {
  return h;
}
inline const Handle_ShapeFix_Root &ShapeFix_Solid_as_root(const Handle_ShapeFix_Solid &h) {
  return h;
}
inline const Handle_ShapeFix_Root &ShapeFix_Shape_as_root(const Handle_ShapeFix_Shape &h) {
  return h;
}

// ---------------------------------------------------------------------------
// ShapeFix_Edge
// ---------------------------------------------------------------------------

inline bool ShapeFix_Edge_FixRemovePCurve_face(const Handle_ShapeFix_Edge &h,
                                               const TopoDS_Edge &edge, const TopoDS_Face &face) {
  try { return h->FixRemovePCurve(edge, face); }
  SHAPEFIX_CATCH
}

inline bool ShapeFix_Edge_FixRemovePCurve_surface(const Handle_ShapeFix_Edge &h,
                                                  const TopoDS_Edge &edge,
                                                  const Handle_Geom_Surface &surface,
                                                  const TopLoc_Location &location) {
  try { return h->FixRemovePCurve(edge, surface, location); }
  SHAPEFIX_CATCH
}

inline bool ShapeFix_Edge_FixRemoveCurve3d(const Handle_ShapeFix_Edge &h, const TopoDS_Edge &edge) {
  try { return h->FixRemoveCurve3d(edge); }
  SHAPEFIX_CATCH
}

inline bool ShapeFix_Edge_FixAddPCurve_face(const Handle_ShapeFix_Edge &h, const TopoDS_Edge &edge,
                                            const TopoDS_Face &face, Standard_Boolean seam,
                                            Standard_Real prec) {
  try { return h->FixAddPCurve(edge, face, seam, prec); }
  SHAPEFIX_CATCH
}

inline bool ShapeFix_Edge_FixAddPCurve_surface(const Handle_ShapeFix_Edge &h,
                                               const TopoDS_Edge &edge,
                                               const Handle_Geom_Surface &surface,
                                               const TopLoc_Location &location, Standard_Boolean seam,
                                               Standard_Real prec) {
  try { return h->FixAddPCurve(edge, surface, location, seam, prec); }
  SHAPEFIX_CATCH
}

inline bool ShapeFix_Edge_FixAddCurve3d(const Handle_ShapeFix_Edge &h, const TopoDS_Edge &edge) {
  try { return h->FixAddCurve3d(edge); }
  SHAPEFIX_CATCH
}

inline bool ShapeFix_Edge_FixVertexTolerance_face(const Handle_ShapeFix_Edge &h,
                                                  const TopoDS_Edge &edge,
                                                  const TopoDS_Face &face) {
  try { return h->FixVertexTolerance(edge, face); }
  SHAPEFIX_CATCH
}

inline bool ShapeFix_Edge_FixVertexTolerance(const Handle_ShapeFix_Edge &h,
                                             const TopoDS_Edge &edge) {
  try { return h->FixVertexTolerance(edge); }
  SHAPEFIX_CATCH
}

inline bool ShapeFix_Edge_FixReversed2d_face(const Handle_ShapeFix_Edge &h,
                                             const TopoDS_Edge &edge, const TopoDS_Face &face) {
  try { return h->FixReversed2d(edge, face); }
  SHAPEFIX_CATCH
}

inline bool ShapeFix_Edge_FixReversed2d_surface(const Handle_ShapeFix_Edge &h,
                                                const TopoDS_Edge &edge,
                                                const Handle_Geom_Surface &surface,
                                                const TopLoc_Location &location) {
  try { return h->FixReversed2d(edge, surface, location); }
  SHAPEFIX_CATCH
}

inline bool ShapeFix_Edge_FixSameParameter(const Handle_ShapeFix_Edge &h, const TopoDS_Edge &edge,
                                           Standard_Real tolerance) {
  try { return h->FixSameParameter(edge, tolerance); }
  SHAPEFIX_CATCH
}

inline bool ShapeFix_Edge_FixSameParameter_face(const Handle_ShapeFix_Edge &h,
                                                const TopoDS_Edge &edge, const TopoDS_Face &face,
                                                Standard_Real tolerance) {
  try { return h->FixSameParameter(edge, face, tolerance); }
  SHAPEFIX_CATCH
}

// ---------------------------------------------------------------------------
// ShapeFix_Wire — action methods
// ---------------------------------------------------------------------------

inline void ShapeFix_Wire_Init(const Handle_ShapeFix_Wire &h, const TopoDS_Wire &wire,
                               const TopoDS_Face &face, Standard_Real prec) {
  try { h->Init(wire, face, prec); }
  SHAPEFIX_CATCH
}

inline void ShapeFix_Wire_Load(const Handle_ShapeFix_Wire &h, const TopoDS_Wire &wire) {
  try { h->Load(wire); }
  SHAPEFIX_CATCH
}

inline void ShapeFix_Wire_SetFace(const Handle_ShapeFix_Wire &h, const TopoDS_Face &face) {
  try { h->SetFace(face); }
  SHAPEFIX_CATCH
}

inline void ShapeFix_Wire_SetSurface(const Handle_ShapeFix_Wire &h,
                                     const Handle_Geom_Surface &surface) {
  try { h->SetSurface(surface); }
  SHAPEFIX_CATCH
}

inline void ShapeFix_Wire_SetSurface_placed(const Handle_ShapeFix_Wire &h,
                                            const Handle_Geom_Surface &surface,
                                            const TopLoc_Location &location) {
  try { h->SetSurface(surface, location); }
  SHAPEFIX_CATCH
}

inline void ShapeFix_Wire_SetMaxTailAngle(const Handle_ShapeFix_Wire &h, Standard_Real value) {
  h->SetMaxTailAngle(value);
}

inline void ShapeFix_Wire_SetMaxTailWidth(const Handle_ShapeFix_Wire &h, Standard_Real value) {
  h->SetMaxTailWidth(value);
}

inline bool ShapeFix_Wire_IsLoaded(const Handle_ShapeFix_Wire &h) { return h->IsLoaded(); }
inline bool ShapeFix_Wire_IsReady(const Handle_ShapeFix_Wire &h) { return h->IsReady(); }
inline Standard_Integer ShapeFix_Wire_NbEdges(const Handle_ShapeFix_Wire &h) { return h->NbEdges(); }

inline std::unique_ptr<TopoDS_Wire> ShapeFix_Wire_Wire(const Handle_ShapeFix_Wire &h) {
  try { return std::unique_ptr<TopoDS_Wire>(new TopoDS_Wire(h->Wire())); }
  SHAPEFIX_CATCH
}

inline std::unique_ptr<TopoDS_Wire> ShapeFix_Wire_WireAPIMake(const Handle_ShapeFix_Wire &h) {
  try { return std::unique_ptr<TopoDS_Wire>(new TopoDS_Wire(h->WireAPIMake())); }
  SHAPEFIX_CATCH
}

inline std::unique_ptr<TopoDS_Face> ShapeFix_Wire_Face(const Handle_ShapeFix_Wire &h) {
  try { return std::unique_ptr<TopoDS_Face>(new TopoDS_Face(h->Face())); }
  SHAPEFIX_CATCH
}

inline bool ShapeFix_Wire_Perform(const Handle_ShapeFix_Wire &h) {
  try { return h->Perform(); }
  SHAPEFIX_CATCH
}

inline void ShapeFix_Wire_ClearModes(const Handle_ShapeFix_Wire &h) { h->ClearModes(); }
inline void ShapeFix_Wire_ClearStatuses(const Handle_ShapeFix_Wire &h) { h->ClearStatuses(); }

inline std::unique_ptr<Handle_ShapeFix_Edge> ShapeFix_Wire_FixEdgeTool(const Handle_ShapeFix_Wire &h) {
  return std::unique_ptr<Handle_ShapeFix_Edge>(new Handle_ShapeFix_Edge(h->FixEdgeTool()));
}

inline bool ShapeFix_Wire_FixReorder(const Handle_ShapeFix_Wire &h) {
  try { return h->FixReorder(); }
  SHAPEFIX_CATCH
}

inline Standard_Integer ShapeFix_Wire_FixSmall_global(const Handle_ShapeFix_Wire &h,
                                                      Standard_Boolean lockvtx, Standard_Real prec) {
  try { return h->FixSmall(lockvtx, prec); }
  SHAPEFIX_CATCH
}

inline bool ShapeFix_Wire_FixSmall_one(const Handle_ShapeFix_Wire &h, Standard_Integer num,
                                       Standard_Boolean lockvtx, Standard_Real prec) {
  try { return h->FixSmall(num, lockvtx, prec); }
  SHAPEFIX_CATCH
}

inline bool ShapeFix_Wire_FixConnected(const Handle_ShapeFix_Wire &h, Standard_Real prec) {
  try { return h->FixConnected(prec); }
  SHAPEFIX_CATCH
}

inline bool ShapeFix_Wire_FixConnected_one(const Handle_ShapeFix_Wire &h, Standard_Integer num,
                                           Standard_Real prec) {
  try { return h->FixConnected(num, prec); }
  SHAPEFIX_CATCH
}

inline bool ShapeFix_Wire_FixEdgeCurves(const Handle_ShapeFix_Wire &h) {
  try { return h->FixEdgeCurves(); }
  SHAPEFIX_CATCH
}

inline bool ShapeFix_Wire_FixDegenerated(const Handle_ShapeFix_Wire &h) {
  try { return h->FixDegenerated(); }
  SHAPEFIX_CATCH
}

inline bool ShapeFix_Wire_FixDegenerated_one(const Handle_ShapeFix_Wire &h, Standard_Integer num) {
  try { return h->FixDegenerated(num); }
  SHAPEFIX_CATCH
}

inline bool ShapeFix_Wire_FixSelfIntersection(const Handle_ShapeFix_Wire &h) {
  try { return h->FixSelfIntersection(); }
  SHAPEFIX_CATCH
}

inline bool ShapeFix_Wire_FixLacking(const Handle_ShapeFix_Wire &h, Standard_Boolean force) {
  try { return h->FixLacking(force); }
  SHAPEFIX_CATCH
}

inline bool ShapeFix_Wire_FixLacking_one(const Handle_ShapeFix_Wire &h, Standard_Integer num,
                                         Standard_Boolean force) {
  try { return h->FixLacking(num, force); }
  SHAPEFIX_CATCH
}

inline bool ShapeFix_Wire_FixClosed(const Handle_ShapeFix_Wire &h, Standard_Real prec) {
  try { return h->FixClosed(prec); }
  SHAPEFIX_CATCH
}

inline bool ShapeFix_Wire_FixGaps3d(const Handle_ShapeFix_Wire &h) {
  try { return h->FixGaps3d(); }
  SHAPEFIX_CATCH
}

inline bool ShapeFix_Wire_FixGaps2d(const Handle_ShapeFix_Wire &h) {
  try { return h->FixGaps2d(); }
  SHAPEFIX_CATCH
}

inline bool ShapeFix_Wire_FixSeam(const Handle_ShapeFix_Wire &h, Standard_Integer num) {
  try { return h->FixSeam(num); }
  SHAPEFIX_CATCH
}

inline bool ShapeFix_Wire_FixShifted(const Handle_ShapeFix_Wire &h) {
  try { return h->FixShifted(); }
  SHAPEFIX_CATCH
}

inline bool ShapeFix_Wire_FixNotchedEdges(const Handle_ShapeFix_Wire &h) {
  try { return h->FixNotchedEdges(); }
  SHAPEFIX_CATCH
}

inline bool ShapeFix_Wire_FixGap3d(const Handle_ShapeFix_Wire &h, Standard_Integer num,
                                   Standard_Boolean convert) {
  try { return h->FixGap3d(num, convert); }
  SHAPEFIX_CATCH
}

inline bool ShapeFix_Wire_FixGap2d(const Handle_ShapeFix_Wire &h, Standard_Integer num,
                                   Standard_Boolean convert) {
  try { return h->FixGap2d(num, convert); }
  SHAPEFIX_CATCH
}

inline bool ShapeFix_Wire_FixTails(const Handle_ShapeFix_Wire &h) {
  try { return h->FixTails(); }
  SHAPEFIX_CATCH
}

// ---------------------------------------------------------------------------
// ShapeFix_Wire — modes
// ---------------------------------------------------------------------------

inline bool ShapeFix_Wire_ModifyTopologyMode(const Handle_ShapeFix_Wire &h) {
  return h->ModifyTopologyMode();
}
inline void ShapeFix_Wire_set_ModifyTopologyMode(const Handle_ShapeFix_Wire &h, bool value) {
  h->ModifyTopologyMode() = value;
}
inline bool ShapeFix_Wire_ModifyGeometryMode(const Handle_ShapeFix_Wire &h) {
  return h->ModifyGeometryMode();
}
inline void ShapeFix_Wire_set_ModifyGeometryMode(const Handle_ShapeFix_Wire &h, bool value) {
  h->ModifyGeometryMode() = value;
}
inline bool ShapeFix_Wire_ClosedWireMode(const Handle_ShapeFix_Wire &h) { return h->ClosedWireMode(); }
inline void ShapeFix_Wire_set_ClosedWireMode(const Handle_ShapeFix_Wire &h, bool value) {
  h->ClosedWireMode() = value;
}
inline bool ShapeFix_Wire_PreferencePCurveMode(const Handle_ShapeFix_Wire &h) {
  return h->PreferencePCurveMode();
}
inline void ShapeFix_Wire_set_PreferencePCurveMode(const Handle_ShapeFix_Wire &h, bool value) {
  h->PreferencePCurveMode() = value;
}
inline bool ShapeFix_Wire_FixGapsByRangesMode(const Handle_ShapeFix_Wire &h) {
  return h->FixGapsByRangesMode();
}
inline void ShapeFix_Wire_set_FixGapsByRangesMode(const Handle_ShapeFix_Wire &h, bool value) {
  h->FixGapsByRangesMode() = value;
}

inline Standard_Integer ShapeFix_Wire_ModifyRemoveLoopMode(const Handle_ShapeFix_Wire &h) {
  return h->ModifyRemoveLoopMode();
}
inline void ShapeFix_Wire_set_ModifyRemoveLoopMode(const Handle_ShapeFix_Wire &h,
                                                   Standard_Integer value) {
  h->ModifyRemoveLoopMode() = value;
}
inline Standard_Integer ShapeFix_Wire_FixReorderMode(const Handle_ShapeFix_Wire &h) {
  return h->FixReorderMode();
}
inline void ShapeFix_Wire_set_FixReorderMode(const Handle_ShapeFix_Wire &h, Standard_Integer value) {
  h->FixReorderMode() = value;
}
inline Standard_Integer ShapeFix_Wire_FixSmallMode(const Handle_ShapeFix_Wire &h) {
  return h->FixSmallMode();
}
inline void ShapeFix_Wire_set_FixSmallMode(const Handle_ShapeFix_Wire &h, Standard_Integer value) {
  h->FixSmallMode() = value;
}
inline Standard_Integer ShapeFix_Wire_FixConnectedMode(const Handle_ShapeFix_Wire &h) {
  return h->FixConnectedMode();
}
inline void ShapeFix_Wire_set_FixConnectedMode(const Handle_ShapeFix_Wire &h,
                                               Standard_Integer value) {
  h->FixConnectedMode() = value;
}
inline Standard_Integer ShapeFix_Wire_FixEdgeCurvesMode(const Handle_ShapeFix_Wire &h) {
  return h->FixEdgeCurvesMode();
}
inline void ShapeFix_Wire_set_FixEdgeCurvesMode(const Handle_ShapeFix_Wire &h,
                                                Standard_Integer value) {
  h->FixEdgeCurvesMode() = value;
}
inline Standard_Integer ShapeFix_Wire_FixDegeneratedMode(const Handle_ShapeFix_Wire &h) {
  return h->FixDegeneratedMode();
}
inline void ShapeFix_Wire_set_FixDegeneratedMode(const Handle_ShapeFix_Wire &h,
                                                 Standard_Integer value) {
  h->FixDegeneratedMode() = value;
}
inline Standard_Integer ShapeFix_Wire_FixSelfIntersectionMode(const Handle_ShapeFix_Wire &h) {
  return h->FixSelfIntersectionMode();
}
inline void ShapeFix_Wire_set_FixSelfIntersectionMode(const Handle_ShapeFix_Wire &h,
                                                      Standard_Integer value) {
  h->FixSelfIntersectionMode() = value;
}
inline Standard_Integer ShapeFix_Wire_FixLackingMode(const Handle_ShapeFix_Wire &h) {
  return h->FixLackingMode();
}
inline void ShapeFix_Wire_set_FixLackingMode(const Handle_ShapeFix_Wire &h, Standard_Integer value) {
  h->FixLackingMode() = value;
}
inline Standard_Integer ShapeFix_Wire_FixGaps3dMode(const Handle_ShapeFix_Wire &h) {
  return h->FixGaps3dMode();
}
inline void ShapeFix_Wire_set_FixGaps3dMode(const Handle_ShapeFix_Wire &h, Standard_Integer value) {
  h->FixGaps3dMode() = value;
}
inline Standard_Integer ShapeFix_Wire_FixGaps2dMode(const Handle_ShapeFix_Wire &h) {
  return h->FixGaps2dMode();
}
inline void ShapeFix_Wire_set_FixGaps2dMode(const Handle_ShapeFix_Wire &h, Standard_Integer value) {
  h->FixGaps2dMode() = value;
}
inline Standard_Integer ShapeFix_Wire_FixReversed2dMode(const Handle_ShapeFix_Wire &h) {
  return h->FixReversed2dMode();
}
inline void ShapeFix_Wire_set_FixReversed2dMode(const Handle_ShapeFix_Wire &h,
                                                Standard_Integer value) {
  h->FixReversed2dMode() = value;
}
inline Standard_Integer ShapeFix_Wire_FixRemovePCurveMode(const Handle_ShapeFix_Wire &h) {
  return h->FixRemovePCurveMode();
}
inline void ShapeFix_Wire_set_FixRemovePCurveMode(const Handle_ShapeFix_Wire &h,
                                                  Standard_Integer value) {
  h->FixRemovePCurveMode() = value;
}
inline Standard_Integer ShapeFix_Wire_FixAddPCurveMode(const Handle_ShapeFix_Wire &h) {
  return h->FixAddPCurveMode();
}
inline void ShapeFix_Wire_set_FixAddPCurveMode(const Handle_ShapeFix_Wire &h,
                                               Standard_Integer value) {
  h->FixAddPCurveMode() = value;
}
inline Standard_Integer ShapeFix_Wire_FixRemoveCurve3dMode(const Handle_ShapeFix_Wire &h) {
  return h->FixRemoveCurve3dMode();
}
inline void ShapeFix_Wire_set_FixRemoveCurve3dMode(const Handle_ShapeFix_Wire &h,
                                                   Standard_Integer value) {
  h->FixRemoveCurve3dMode() = value;
}
inline Standard_Integer ShapeFix_Wire_FixAddCurve3dMode(const Handle_ShapeFix_Wire &h) {
  return h->FixAddCurve3dMode();
}
inline void ShapeFix_Wire_set_FixAddCurve3dMode(const Handle_ShapeFix_Wire &h,
                                                Standard_Integer value) {
  h->FixAddCurve3dMode() = value;
}
inline Standard_Integer ShapeFix_Wire_FixSeamMode(const Handle_ShapeFix_Wire &h) {
  return h->FixSeamMode();
}
inline void ShapeFix_Wire_set_FixSeamMode(const Handle_ShapeFix_Wire &h, Standard_Integer value) {
  h->FixSeamMode() = value;
}
inline Standard_Integer ShapeFix_Wire_FixShiftedMode(const Handle_ShapeFix_Wire &h) {
  return h->FixShiftedMode();
}
inline void ShapeFix_Wire_set_FixShiftedMode(const Handle_ShapeFix_Wire &h, Standard_Integer value) {
  h->FixShiftedMode() = value;
}
inline Standard_Integer ShapeFix_Wire_FixSameParameterMode(const Handle_ShapeFix_Wire &h) {
  return h->FixSameParameterMode();
}
inline void ShapeFix_Wire_set_FixSameParameterMode(const Handle_ShapeFix_Wire &h,
                                                   Standard_Integer value) {
  h->FixSameParameterMode() = value;
}
inline Standard_Integer ShapeFix_Wire_FixVertexToleranceMode(const Handle_ShapeFix_Wire &h) {
  return h->FixVertexToleranceMode();
}
inline void ShapeFix_Wire_set_FixVertexToleranceMode(const Handle_ShapeFix_Wire &h,
                                                     Standard_Integer value) {
  h->FixVertexToleranceMode() = value;
}
inline Standard_Integer ShapeFix_Wire_FixNotchedEdgesMode(const Handle_ShapeFix_Wire &h) {
  return h->FixNotchedEdgesMode();
}
inline void ShapeFix_Wire_set_FixNotchedEdgesMode(const Handle_ShapeFix_Wire &h,
                                                  Standard_Integer value) {
  h->FixNotchedEdgesMode() = value;
}
inline Standard_Integer ShapeFix_Wire_FixSelfIntersectingEdgeMode(const Handle_ShapeFix_Wire &h) {
  return h->FixSelfIntersectingEdgeMode();
}
inline void ShapeFix_Wire_set_FixSelfIntersectingEdgeMode(const Handle_ShapeFix_Wire &h,
                                                          Standard_Integer value) {
  h->FixSelfIntersectingEdgeMode() = value;
}
inline Standard_Integer ShapeFix_Wire_FixIntersectingEdgesMode(const Handle_ShapeFix_Wire &h) {
  return h->FixIntersectingEdgesMode();
}
inline void ShapeFix_Wire_set_FixIntersectingEdgesMode(const Handle_ShapeFix_Wire &h,
                                                       Standard_Integer value) {
  h->FixIntersectingEdgesMode() = value;
}
inline Standard_Integer ShapeFix_Wire_FixNonAdjacentIntersectingEdgesMode(
    const Handle_ShapeFix_Wire &h) {
  return h->FixNonAdjacentIntersectingEdgesMode();
}
inline void ShapeFix_Wire_set_FixNonAdjacentIntersectingEdgesMode(const Handle_ShapeFix_Wire &h,
                                                                  Standard_Integer value) {
  h->FixNonAdjacentIntersectingEdgesMode() = value;
}
inline Standard_Integer ShapeFix_Wire_FixTailMode(const Handle_ShapeFix_Wire &h) {
  return h->FixTailMode();
}
inline void ShapeFix_Wire_set_FixTailMode(const Handle_ShapeFix_Wire &h, Standard_Integer value) {
  h->FixTailMode() = value;
}

// ---------------------------------------------------------------------------
// ShapeFix_Face
// ---------------------------------------------------------------------------

inline void ShapeFix_Face_Init(const Handle_ShapeFix_Face &h, const TopoDS_Face &face) {
  try { h->Init(face); }
  SHAPEFIX_CATCH
}

inline void ShapeFix_Face_Init_surface(const Handle_ShapeFix_Face &h,
                                       const Handle_Geom_Surface &surface, Standard_Real prec,
                                       Standard_Boolean fwd) {
  try { h->Init(surface, prec, fwd); }
  SHAPEFIX_CATCH
}

inline void ShapeFix_Face_Add(const Handle_ShapeFix_Face &h, const TopoDS_Wire &wire) {
  try { h->Add(wire); }
  SHAPEFIX_CATCH
}

inline bool ShapeFix_Face_Perform(const Handle_ShapeFix_Face &h) {
  try { return h->Perform(); }
  SHAPEFIX_CATCH
}

inline bool ShapeFix_Face_FixOrientation(const Handle_ShapeFix_Face &h) {
  try { return h->FixOrientation(); }
  SHAPEFIX_CATCH
}

inline bool ShapeFix_Face_FixAddNaturalBound(const Handle_ShapeFix_Face &h) {
  try { return h->FixAddNaturalBound(); }
  SHAPEFIX_CATCH
}

inline bool ShapeFix_Face_FixMissingSeam(const Handle_ShapeFix_Face &h) {
  try { return h->FixMissingSeam(); }
  SHAPEFIX_CATCH
}

inline bool ShapeFix_Face_FixSmallAreaWire(const Handle_ShapeFix_Face &h,
                                           Standard_Boolean remove_small_face) {
  try { return h->FixSmallAreaWire(remove_small_face); }
  SHAPEFIX_CATCH
}

inline bool ShapeFix_Face_FixIntersectingWires(const Handle_ShapeFix_Face &h) {
  try { return h->FixIntersectingWires(); }
  SHAPEFIX_CATCH
}

inline bool ShapeFix_Face_FixWiresTwoCoincEdges(const Handle_ShapeFix_Face &h) {
  try { return h->FixWiresTwoCoincEdges(); }
  SHAPEFIX_CATCH
}

inline bool ShapeFix_Face_FixPeriodicDegenerated(const Handle_ShapeFix_Face &h) {
  try { return h->FixPeriodicDegenerated(); }
  SHAPEFIX_CATCH
}

inline std::unique_ptr<TopoDS_Face> ShapeFix_Face_Face(const Handle_ShapeFix_Face &h) {
  try { return std::unique_ptr<TopoDS_Face>(new TopoDS_Face(h->Face())); }
  SHAPEFIX_CATCH
}

inline std::unique_ptr<TopoDS_Shape> ShapeFix_Face_Result(const Handle_ShapeFix_Face &h) {
  try { return std::unique_ptr<TopoDS_Shape>(new TopoDS_Shape(h->Result())); }
  SHAPEFIX_CATCH
}

inline std::unique_ptr<Handle_ShapeFix_Wire> ShapeFix_Face_FixWireTool(const Handle_ShapeFix_Face &h) {
  return std::unique_ptr<Handle_ShapeFix_Wire>(new Handle_ShapeFix_Wire(h->FixWireTool()));
}

inline void ShapeFix_Face_ClearModes(const Handle_ShapeFix_Face &h) { h->ClearModes(); }

inline Standard_Integer ShapeFix_Face_FixWireMode(const Handle_ShapeFix_Face &h) {
  return h->FixWireMode();
}
inline void ShapeFix_Face_set_FixWireMode(const Handle_ShapeFix_Face &h, Standard_Integer value) {
  h->FixWireMode() = value;
}
inline Standard_Integer ShapeFix_Face_FixOrientationMode(const Handle_ShapeFix_Face &h) {
  return h->FixOrientationMode();
}
inline void ShapeFix_Face_set_FixOrientationMode(const Handle_ShapeFix_Face &h,
                                                 Standard_Integer value) {
  h->FixOrientationMode() = value;
}
inline Standard_Integer ShapeFix_Face_FixAddNaturalBoundMode(const Handle_ShapeFix_Face &h) {
  return h->FixAddNaturalBoundMode();
}
inline void ShapeFix_Face_set_FixAddNaturalBoundMode(const Handle_ShapeFix_Face &h,
                                                     Standard_Integer value) {
  h->FixAddNaturalBoundMode() = value;
}
inline Standard_Integer ShapeFix_Face_FixMissingSeamMode(const Handle_ShapeFix_Face &h) {
  return h->FixMissingSeamMode();
}
inline void ShapeFix_Face_set_FixMissingSeamMode(const Handle_ShapeFix_Face &h,
                                                 Standard_Integer value) {
  h->FixMissingSeamMode() = value;
}
inline Standard_Integer ShapeFix_Face_FixSmallAreaWireMode(const Handle_ShapeFix_Face &h) {
  return h->FixSmallAreaWireMode();
}
inline void ShapeFix_Face_set_FixSmallAreaWireMode(const Handle_ShapeFix_Face &h,
                                                   Standard_Integer value) {
  h->FixSmallAreaWireMode() = value;
}
inline Standard_Integer ShapeFix_Face_RemoveSmallAreaFaceMode(const Handle_ShapeFix_Face &h) {
  return h->RemoveSmallAreaFaceMode();
}
inline void ShapeFix_Face_set_RemoveSmallAreaFaceMode(const Handle_ShapeFix_Face &h,
                                                      Standard_Integer value) {
  h->RemoveSmallAreaFaceMode() = value;
}
inline Standard_Integer ShapeFix_Face_FixIntersectingWiresMode(const Handle_ShapeFix_Face &h) {
  return h->FixIntersectingWiresMode();
}
inline void ShapeFix_Face_set_FixIntersectingWiresMode(const Handle_ShapeFix_Face &h,
                                                       Standard_Integer value) {
  h->FixIntersectingWiresMode() = value;
}
inline Standard_Integer ShapeFix_Face_FixLoopWiresMode(const Handle_ShapeFix_Face &h) {
  return h->FixLoopWiresMode();
}
inline void ShapeFix_Face_set_FixLoopWiresMode(const Handle_ShapeFix_Face &h,
                                               Standard_Integer value) {
  h->FixLoopWiresMode() = value;
}
inline Standard_Integer ShapeFix_Face_FixSplitFaceMode(const Handle_ShapeFix_Face &h) {
  return h->FixSplitFaceMode();
}
inline void ShapeFix_Face_set_FixSplitFaceMode(const Handle_ShapeFix_Face &h,
                                               Standard_Integer value) {
  h->FixSplitFaceMode() = value;
}
inline Standard_Integer ShapeFix_Face_AutoCorrectPrecisionMode(const Handle_ShapeFix_Face &h) {
  return h->AutoCorrectPrecisionMode();
}
inline void ShapeFix_Face_set_AutoCorrectPrecisionMode(const Handle_ShapeFix_Face &h,
                                                       Standard_Integer value) {
  h->AutoCorrectPrecisionMode() = value;
}
inline Standard_Integer ShapeFix_Face_FixPeriodicDegeneratedMode(const Handle_ShapeFix_Face &h) {
  return h->FixPeriodicDegeneratedMode();
}
inline void ShapeFix_Face_set_FixPeriodicDegeneratedMode(const Handle_ShapeFix_Face &h,
                                                         Standard_Integer value) {
  h->FixPeriodicDegeneratedMode() = value;
}

// ---------------------------------------------------------------------------
// ShapeFix_Shell
// ---------------------------------------------------------------------------

inline void ShapeFix_Shell_Init(const Handle_ShapeFix_Shell &h, const TopoDS_Shell &shell) {
  try { h->Init(shell); }
  SHAPEFIX_CATCH
}

inline bool ShapeFix_Shell_Perform(const Handle_ShapeFix_Shell &h) {
  try { return h->Perform(); }
  SHAPEFIX_CATCH
}

inline std::unique_ptr<TopoDS_Shell> ShapeFix_Shell_Shell(const Handle_ShapeFix_Shell &h) {
  try { return std::unique_ptr<TopoDS_Shell>(new TopoDS_Shell(h->Shell())); }
  SHAPEFIX_CATCH
}

inline std::unique_ptr<TopoDS_Shape> ShapeFix_Shell_Shape(const Handle_ShapeFix_Shell &h) {
  try { return std::unique_ptr<TopoDS_Shape>(new TopoDS_Shape(h->Shape())); }
  SHAPEFIX_CATCH
}

inline std::unique_ptr<TopoDS_Compound> ShapeFix_Shell_ErrorFaces(const Handle_ShapeFix_Shell &h) {
  try { return std::unique_ptr<TopoDS_Compound>(new TopoDS_Compound(h->ErrorFaces())); }
  SHAPEFIX_CATCH
}

inline Standard_Integer ShapeFix_Shell_NbShells(const Handle_ShapeFix_Shell &h) {
  return h->NbShells();
}

inline std::unique_ptr<Handle_ShapeFix_Face> ShapeFix_Shell_FixFaceTool(const Handle_ShapeFix_Shell &h) {
  return std::unique_ptr<Handle_ShapeFix_Face>(new Handle_ShapeFix_Face(h->FixFaceTool()));
}

inline bool ShapeFix_Shell_FixFaceOrientation(const Handle_ShapeFix_Shell &h,
                                              const TopoDS_Shell &shell,
                                              Standard_Boolean multi_conex,
                                              Standard_Boolean non_manifold) {
  try { return h->FixFaceOrientation(shell, multi_conex, non_manifold); }
  SHAPEFIX_CATCH
}

inline void ShapeFix_Shell_SetNonManifoldFlag(const Handle_ShapeFix_Shell &h, bool value) {
  h->SetNonManifoldFlag(value);
}

inline Standard_Integer ShapeFix_Shell_FixFaceMode(const Handle_ShapeFix_Shell &h) {
  return h->FixFaceMode();
}
inline void ShapeFix_Shell_set_FixFaceMode(const Handle_ShapeFix_Shell &h, Standard_Integer value) {
  h->FixFaceMode() = value;
}
inline Standard_Integer ShapeFix_Shell_FixOrientationMode(const Handle_ShapeFix_Shell &h) {
  return h->FixOrientationMode();
}
inline void ShapeFix_Shell_set_FixOrientationMode(const Handle_ShapeFix_Shell &h,
                                                  Standard_Integer value) {
  h->FixOrientationMode() = value;
}

// ---------------------------------------------------------------------------
// ShapeFix_Solid
// ---------------------------------------------------------------------------

inline void ShapeFix_Solid_Init(const Handle_ShapeFix_Solid &h, const TopoDS_Solid &solid) {
  try { h->Init(solid); }
  SHAPEFIX_CATCH
}

inline bool ShapeFix_Solid_Perform(const Handle_ShapeFix_Solid &h) {
  try { return h->Perform(); }
  SHAPEFIX_CATCH
}

inline std::unique_ptr<TopoDS_Solid> ShapeFix_Solid_SolidFromShell(const Handle_ShapeFix_Solid &h,
                                                                   const TopoDS_Shell &shell) {
  try { return std::unique_ptr<TopoDS_Solid>(new TopoDS_Solid(h->SolidFromShell(shell))); }
  SHAPEFIX_CATCH
}

inline std::unique_ptr<TopoDS_Shape> ShapeFix_Solid_Solid(const Handle_ShapeFix_Solid &h) {
  try { return std::unique_ptr<TopoDS_Shape>(new TopoDS_Shape(h->Solid())); }
  SHAPEFIX_CATCH
}

inline std::unique_ptr<TopoDS_Shape> ShapeFix_Solid_Shape(const Handle_ShapeFix_Solid &h) {
  try { return std::unique_ptr<TopoDS_Shape>(new TopoDS_Shape(h->Shape())); }
  SHAPEFIX_CATCH
}

inline std::unique_ptr<Handle_ShapeFix_Shell> ShapeFix_Solid_FixShellTool(const Handle_ShapeFix_Solid &h) {
  return std::unique_ptr<Handle_ShapeFix_Shell>(new Handle_ShapeFix_Shell(h->FixShellTool()));
}

inline Standard_Integer ShapeFix_Solid_FixShellMode(const Handle_ShapeFix_Solid &h) {
  return h->FixShellMode();
}
inline void ShapeFix_Solid_set_FixShellMode(const Handle_ShapeFix_Solid &h, Standard_Integer value) {
  h->FixShellMode() = value;
}
inline Standard_Integer ShapeFix_Solid_FixShellOrientationMode(const Handle_ShapeFix_Solid &h) {
  return h->FixShellOrientationMode();
}
inline void ShapeFix_Solid_set_FixShellOrientationMode(const Handle_ShapeFix_Solid &h,
                                                       Standard_Integer value) {
  h->FixShellOrientationMode() = value;
}
inline bool ShapeFix_Solid_CreateOpenSolidMode(const Handle_ShapeFix_Solid &h) {
  return h->CreateOpenSolidMode();
}
inline void ShapeFix_Solid_set_CreateOpenSolidMode(const Handle_ShapeFix_Solid &h, bool value) {
  h->CreateOpenSolidMode() = value;
}

// ---------------------------------------------------------------------------
// ShapeFix_Shape
// ---------------------------------------------------------------------------

inline void ShapeFix_Shape_Init(const Handle_ShapeFix_Shape &h, const TopoDS_Shape &shape) {
  try { h->Init(shape); }
  SHAPEFIX_CATCH
}

inline bool ShapeFix_Shape_Perform(const Handle_ShapeFix_Shape &h) {
  try { return h->Perform(); }
  SHAPEFIX_CATCH
}

inline std::unique_ptr<TopoDS_Shape> ShapeFix_Shape_Shape(const Handle_ShapeFix_Shape &h) {
  try { return std::unique_ptr<TopoDS_Shape>(new TopoDS_Shape(h->Shape())); }
  SHAPEFIX_CATCH
}

inline std::unique_ptr<Handle_ShapeFix_Solid> ShapeFix_Shape_FixSolidTool(
    const Handle_ShapeFix_Shape &h) {
  return std::unique_ptr<Handle_ShapeFix_Solid>(new Handle_ShapeFix_Solid(h->FixSolidTool()));
}

inline std::unique_ptr<Handle_ShapeFix_Shell> ShapeFix_Shape_FixShellTool(
    const Handle_ShapeFix_Shape &h) {
  return std::unique_ptr<Handle_ShapeFix_Shell>(new Handle_ShapeFix_Shell(h->FixShellTool()));
}

inline std::unique_ptr<Handle_ShapeFix_Face> ShapeFix_Shape_FixFaceTool(
    const Handle_ShapeFix_Shape &h) {
  return std::unique_ptr<Handle_ShapeFix_Face>(new Handle_ShapeFix_Face(h->FixFaceTool()));
}

inline std::unique_ptr<Handle_ShapeFix_Wire> ShapeFix_Shape_FixWireTool(
    const Handle_ShapeFix_Shape &h) {
  return std::unique_ptr<Handle_ShapeFix_Wire>(new Handle_ShapeFix_Wire(h->FixWireTool()));
}

inline std::unique_ptr<Handle_ShapeFix_Edge> ShapeFix_Shape_FixEdgeTool(
    const Handle_ShapeFix_Shape &h) {
  return std::unique_ptr<Handle_ShapeFix_Edge>(new Handle_ShapeFix_Edge(h->FixEdgeTool()));
}

inline Standard_Integer ShapeFix_Shape_FixSolidMode(const Handle_ShapeFix_Shape &h) {
  return h->FixSolidMode();
}
inline void ShapeFix_Shape_set_FixSolidMode(const Handle_ShapeFix_Shape &h, Standard_Integer value) {
  h->FixSolidMode() = value;
}
inline Standard_Integer ShapeFix_Shape_FixFreeShellMode(const Handle_ShapeFix_Shape &h) {
  return h->FixFreeShellMode();
}
inline void ShapeFix_Shape_set_FixFreeShellMode(const Handle_ShapeFix_Shape &h,
                                                Standard_Integer value) {
  h->FixFreeShellMode() = value;
}
inline Standard_Integer ShapeFix_Shape_FixFreeFaceMode(const Handle_ShapeFix_Shape &h) {
  return h->FixFreeFaceMode();
}
inline void ShapeFix_Shape_set_FixFreeFaceMode(const Handle_ShapeFix_Shape &h,
                                               Standard_Integer value) {
  h->FixFreeFaceMode() = value;
}
inline Standard_Integer ShapeFix_Shape_FixFreeWireMode(const Handle_ShapeFix_Shape &h) {
  return h->FixFreeWireMode();
}
inline void ShapeFix_Shape_set_FixFreeWireMode(const Handle_ShapeFix_Shape &h,
                                               Standard_Integer value) {
  h->FixFreeWireMode() = value;
}
inline Standard_Integer ShapeFix_Shape_FixSameParameterMode(const Handle_ShapeFix_Shape &h) {
  return h->FixSameParameterMode();
}
inline void ShapeFix_Shape_set_FixSameParameterMode(const Handle_ShapeFix_Shape &h,
                                                    Standard_Integer value) {
  h->FixSameParameterMode() = value;
}
inline Standard_Integer ShapeFix_Shape_FixVertexPositionMode(const Handle_ShapeFix_Shape &h) {
  return h->FixVertexPositionMode();
}
inline void ShapeFix_Shape_set_FixVertexPositionMode(const Handle_ShapeFix_Shape &h,
                                                     Standard_Integer value) {
  h->FixVertexPositionMode() = value;
}
inline Standard_Integer ShapeFix_Shape_FixVertexTolMode(const Handle_ShapeFix_Shape &h) {
  return h->FixVertexTolMode();
}
inline void ShapeFix_Shape_set_FixVertexTolMode(const Handle_ShapeFix_Shape &h,
                                                Standard_Integer value) {
  h->FixVertexTolMode() = value;
}
