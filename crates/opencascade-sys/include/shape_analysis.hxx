#include <ShapeAnalysis.hxx>
#include <ShapeAnalysis_FreeBounds.hxx>
#include <ShapeAnalysis_ShapeTolerance.hxx>
#include <Standard_Failure.hxx>
#include <TopAbs_ShapeEnum.hxx>
#include <TopTools_HSequenceOfShape.hxx>
#include <bindings_common.hxx>

// MSVC only: same reasoning
// as the other wrappers here - a static-method function pointer doesn't
// exact-match `Handle_TopTools_HSequenceOfShape` against OCCT's own
// `Handle(TopTools_HSequenceOfShape)&`-typed parameters.
inline void ShapeAnalysis_FreeBounds_ConnectEdgesToWires(Handle_TopTools_HSequenceOfShape &edges,
                                                          Standard_Real tolerance, Standard_Boolean shared,
                                                          Handle_TopTools_HSequenceOfShape &wires) {
  ShapeAnalysis_FreeBounds::ConnectEdgesToWires(edges, tolerance, shared, wires);
}

inline std::unique_ptr<ShapeAnalysis_ShapeTolerance> ShapeAnalysis_ShapeTolerance_new() {
  return std::unique_ptr<ShapeAnalysis_ShapeTolerance>(new ShapeAnalysis_ShapeTolerance());
}

inline void ShapeAnalysis_ShapeTolerance_Tolerance(ShapeAnalysis_ShapeTolerance &analysis,
                                                   const TopoDS_Shape &shape, Standard_Integer mode,
                                                   TopAbs_ShapeEnum shape_type) {
  analysis.Tolerance(shape, mode, shape_type);
}

inline Standard_Real ShapeAnalysis_ShapeTolerance_GlobalTolerance(const ShapeAnalysis_ShapeTolerance &analysis,
                                                                  Standard_Integer mode) {
  return analysis.GlobalTolerance(mode);
}

inline std::unique_ptr<Handle_TopTools_HSequenceOfShape>
ShapeAnalysis_ShapeTolerance_OverTolerance(const ShapeAnalysis_ShapeTolerance &analysis,
                                           const TopoDS_Shape &shape, Standard_Real value,
                                           TopAbs_ShapeEnum shape_type) {
  return std::unique_ptr<Handle_TopTools_HSequenceOfShape>(
      new Handle_TopTools_HSequenceOfShape(analysis.OverTolerance(shape, value, shape_type)));
}

inline std::unique_ptr<Handle_TopTools_HSequenceOfShape>
ShapeAnalysis_ShapeTolerance_InTolerance(const ShapeAnalysis_ShapeTolerance &analysis,
                                         const TopoDS_Shape &shape, Standard_Real valmin,
                                         Standard_Real valmax, TopAbs_ShapeEnum shape_type) {
  return std::unique_ptr<Handle_TopTools_HSequenceOfShape>(
      new Handle_TopTools_HSequenceOfShape(analysis.InTolerance(shape, valmin, valmax, shape_type)));
}
