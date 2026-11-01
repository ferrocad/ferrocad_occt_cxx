#include <ShapeAnalysis.hxx>
#include <ShapeAnalysis_FreeBounds.hxx>
#include <ShapeAnalysis_FreeBoundsProperties.hxx>
#include <ShapeAnalysis_FreeBoundData.hxx>
#include <ShapeAnalysis_ShapeTolerance.hxx>
#include <ShapeAnalysis_Shell.hxx>
#include <ShapeAnalysis_Surface.hxx>
#include <Geom_Surface.hxx>
#include <Standard_Failure.hxx>
#include <TopAbs_ShapeEnum.hxx>
#include <TopTools_HSequenceOfShape.hxx>
#include <TopoDS_Compound.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS_Wire.hxx>
#include <gp_Pnt.hxx>
#include <gp_Pnt2d.hxx>
#include <bindings_common.hxx>
#include <stdexcept>

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

inline std::unique_ptr<ShapeAnalysis_Shell> ShapeAnalysis_Shell_new() {
  return std::unique_ptr<ShapeAnalysis_Shell>(new ShapeAnalysis_Shell());
}

inline void ShapeAnalysis_Shell_LoadShells(ShapeAnalysis_Shell &analysis,
                                           const TopoDS_Shape &shape) {
  analysis.LoadShells(shape);
}

inline void ShapeAnalysis_Shell_CheckOrientedShells(ShapeAnalysis_Shell &analysis,
                                                    const TopoDS_Shape &shape) {
  analysis.CheckOrientedShells(shape, Standard_True, Standard_True);
}

inline std::unique_ptr<TopoDS_Compound>
ShapeAnalysis_Shell_FreeEdges(ShapeAnalysis_Shell &analysis) {
  return std::unique_ptr<TopoDS_Compound>(new TopoDS_Compound(analysis.FreeEdges()));
}

inline std::unique_ptr<ShapeAnalysis_Surface>
ShapeAnalysis_Surface_new(const Handle_Geom_Surface &surface) {
  try {
    return std::unique_ptr<ShapeAnalysis_Surface>(new ShapeAnalysis_Surface(surface));
  } catch (const Standard_Failure &e) {
    const char *msg = e.GetMessageString();
    throw std::runtime_error(msg ? msg : "OpenCASCADE Standard_Failure");
  }
}

inline std::unique_ptr<gp_Pnt2d>
ShapeAnalysis_Surface_ValueOfUV(ShapeAnalysis_Surface &analysis, const gp_Pnt &point,
                                double tolerance) {
  try {
    return std::unique_ptr<gp_Pnt2d>(new gp_Pnt2d(analysis.ValueOfUV(point, tolerance)));
  } catch (const Standard_Failure &e) {
    const char *msg = e.GetMessageString();
    throw std::runtime_error(msg ? msg : "OpenCASCADE Standard_Failure");
  }
}

inline std::unique_ptr<ShapeAnalysis_FreeBoundsProperties>
ShapeAnalysis_FreeBoundsProperties_new(const TopoDS_Shape &shape) {
  try {
    return std::unique_ptr<ShapeAnalysis_FreeBoundsProperties>(
        new ShapeAnalysis_FreeBoundsProperties(shape));
  } catch (const Standard_Failure &e) {
    const char *msg = e.GetMessageString();
    throw std::runtime_error(msg ? msg : "OpenCASCADE Standard_Failure");
  }
}

inline void ShapeAnalysis_FreeBoundsProperties_Perform(ShapeAnalysis_FreeBoundsProperties &analysis) {
  try {
    analysis.Perform();
  } catch (const Standard_Failure &e) {
    const char *msg = e.GetMessageString();
    throw std::runtime_error(msg ? msg : "OpenCASCADE Standard_Failure");
  }
}

inline int ShapeAnalysis_FreeBoundsProperties_NbClosedFreeBounds(
    const ShapeAnalysis_FreeBoundsProperties &analysis) {
  return analysis.NbClosedFreeBounds();
}

inline std::unique_ptr<TopoDS_Wire>
ShapeAnalysis_FreeBoundsProperties_ClosedFreeBound(const ShapeAnalysis_FreeBoundsProperties &analysis,
                                                   int index) {
  try {
    opencascade::handle<ShapeAnalysis_FreeBoundData> data = analysis.ClosedFreeBound(index);
    if (data.IsNull())
      return nullptr;
    return std::unique_ptr<TopoDS_Wire>(new TopoDS_Wire(data->FreeBound()));
  } catch (const Standard_Failure &e) {
    const char *msg = e.GetMessageString();
    throw std::runtime_error(msg ? msg : "OpenCASCADE Standard_Failure");
  }
}
