#include <BRepLib.hxx>
#include <BRepLib_FindSurface.hxx>
#include <GeomAbs_Shape.hxx>
#include <BRepLib_ToolTriangulatedShape.hxx>
#include <Geom_Surface.hxx>
#include <Standard_Failure.hxx>
#include <TopTools_ListOfShape.hxx>
#include <TopoDS_Shape.hxx>
#include <bindings_common.hxx>
#include <stdexcept>

inline void b_rep_lib_rethrow(const Standard_Failure &e) {
  const char *msg = e.GetMessageString();
  throw std::runtime_error(msg ? msg : "OpenCASCADE Standard_Failure");
}

// MSVC only: `Handle_Poly_Triangulation` is a distinct subclass of
// `opencascade::handle<Poly_Triangulation>` there (see
// Standard_Handle.hxx), so a function pointer to
// `BRepLib_ToolTriangulatedShape::ComputeNormals` (declared with
// `Handle(Poly_Triangulation)`, i.e. the base type) doesn't exact-match a
// `Handle_Poly_Triangulation` parameter. An inline wrapper sidesteps the
// function-pointer binding entirely; the implicit conversion at the call
// site is fine either way.
inline void BRepLib_ToolTriangulatedShape_ComputeNormals(const TopoDS_Face &face,
                                                          const Handle_Poly_Triangulation &triangulation) {
  BRepLib_ToolTriangulatedShape::ComputeNormals(face, triangulation);
}

inline bool BRepLib_BuildCurves3d_full(const TopoDS_Shape &shape, double tol,
                                       GeomAbs_Shape continuity, int max_degree, int max_segment) {
  try {
    return BRepLib::BuildCurves3d(shape, tol, continuity, max_degree, max_segment);
  } catch (const Standard_Failure &e) {
    b_rep_lib_rethrow(e);
    return false;
  }
}

inline void BRepLib_BuildPCurveForEdgesOnPlane(const TopTools_ListOfShape &edges,
                                               const TopoDS_Face &face) {
  try {
    BRepLib::BuildPCurveForEdgesOnPlane(edges, face);
  } catch (const Standard_Failure &e) {
    b_rep_lib_rethrow(e);
  }
}

inline void BRepLib_SameRange(const TopoDS_Edge &edge, double tolerance) {
  try {
    BRepLib::SameRange(edge, tolerance);
  } catch (const Standard_Failure &e) {
    b_rep_lib_rethrow(e);
  }
}

inline std::unique_ptr<Handle_Geom_Surface>
BRepLib_FindSurface_Surface(const BRepLib_FindSurface &finder) {
  return std::unique_ptr<Handle_Geom_Surface>(new Handle_Geom_Surface(finder.Surface()));
}
