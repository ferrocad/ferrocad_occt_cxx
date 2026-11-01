#include <BRepBuilderAPI_Copy.hxx>
#include <BRepBuilderAPI_GTransform.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepBuilderAPI_MakeShapeOnMesh.hxx>
#include <BRepBuilderAPI_MakeSolid.hxx>
#include <BRepBuilderAPI_MakeVertex.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepBuilderAPI_NurbsConvert.hxx>
#include <BRepBuilderAPI_Sewing.hxx>
#include <BRepBuilderAPI_Transform.hxx>
#include <BRepBuilderAPI_WireError.hxx>
#include <Geom2d_Curve.hxx>
#include <Geom_Curve.hxx>
#include <Geom_Surface.hxx>
#include <Standard_Failure.hxx>
#include <gp_Pln.hxx>
#include <bindings_common.hxx>
#include <stdexcept>

inline void b_rep_builder_api_rethrow(const Standard_Failure &e) {
  const char *msg = e.GetMessageString();
  throw std::runtime_error(msg ? msg : "OpenCASCADE Standard_Failure");
}

inline std::unique_ptr<BRepBuilderAPI_MakeEdge>
BRepBuilderAPI_MakeEdge_CurveRange(const Handle_Geom_Curve &curve, double first, double last) {
  try {
    return std::unique_ptr<BRepBuilderAPI_MakeEdge>(
        new BRepBuilderAPI_MakeEdge(curve, first, last));
  } catch (const Standard_Failure &e) {
    b_rep_builder_api_rethrow(e);
    return nullptr;
  }
}

inline std::unique_ptr<BRepBuilderAPI_MakeEdge>
BRepBuilderAPI_MakeEdge_CurveSurface2dRange(const Handle_Geom2d_Curve &curve,
                                            const Handle_Geom_Surface &surface, double first,
                                            double last) {
  try {
    return std::unique_ptr<BRepBuilderAPI_MakeEdge>(
        new BRepBuilderAPI_MakeEdge(curve, surface, first, last));
  } catch (const Standard_Failure &e) {
    b_rep_builder_api_rethrow(e);
    return nullptr;
  }
}

inline std::unique_ptr<BRepBuilderAPI_MakeFace>
BRepBuilderAPI_MakeFace_Plane(const gp_Pln &plane, double u1, double u2, double v1, double v2) {
  try {
    return std::unique_ptr<BRepBuilderAPI_MakeFace>(
        new BRepBuilderAPI_MakeFace(plane, u1, u2, v1, v2));
  } catch (const Standard_Failure &e) {
    b_rep_builder_api_rethrow(e);
    return nullptr;
  }
}

inline std::unique_ptr<BRepBuilderAPI_MakeFace>
BRepBuilderAPI_MakeFace_surface_wire(const Handle_Geom_Surface &surface, const TopoDS_Wire &wire,
                                     bool inside) {
  try {
    return std::unique_ptr<BRepBuilderAPI_MakeFace>(
        new BRepBuilderAPI_MakeFace(surface, wire, inside));
  } catch (const Standard_Failure &e) {
    b_rep_builder_api_rethrow(e);
    return nullptr;
  }
}

inline std::unique_ptr<BRepBuilderAPI_MakeFace>
BRepBuilderAPI_MakeFace_surface_range(const Handle_Geom_Surface &surface, double u1, double u2,
                                      double v1, double v2, double tol) {
  try {
    return std::unique_ptr<BRepBuilderAPI_MakeFace>(
        new BRepBuilderAPI_MakeFace(surface, u1, u2, v1, v2, tol));
  } catch (const Standard_Failure &e) {
    b_rep_builder_api_rethrow(e);
    return nullptr;
  }
}

inline std::unique_ptr<BRepBuilderAPI_Sewing> BRepBuilderAPI_Sewing_new(double tolerance) {
  return std::unique_ptr<BRepBuilderAPI_Sewing>(new BRepBuilderAPI_Sewing(tolerance));
}

inline std::unique_ptr<BRepBuilderAPI_Sewing> BRepBuilderAPI_Sewing_new_default() {
  return std::unique_ptr<BRepBuilderAPI_Sewing>(new BRepBuilderAPI_Sewing());
}

inline void BRepBuilderAPI_Sewing_Perform(BRepBuilderAPI_Sewing &sewing) {
  try {
    sewing.Perform();
  } catch (const Standard_Failure &e) {
    b_rep_builder_api_rethrow(e);
  }
}

inline std::unique_ptr<BRepBuilderAPI_NurbsConvert>
BRepBuilderAPI_NurbsConvert_new(const TopoDS_Shape &shape) {
  return std::unique_ptr<BRepBuilderAPI_NurbsConvert>(new BRepBuilderAPI_NurbsConvert(shape));
}

inline std::unique_ptr<BRepBuilderAPI_MakeFace>
BRepBuilderAPI_MakeFace_Plane_wire(const gp_Pln &plane, const TopoDS_Wire &wire, bool inside) {
  try {
    return std::unique_ptr<BRepBuilderAPI_MakeFace>(
        new BRepBuilderAPI_MakeFace(plane, wire, inside));
  } catch (const Standard_Failure &e) {
    b_rep_builder_api_rethrow(e);
    return nullptr;
  }
}

inline void BRepBuilderAPI_Sewing_Add(BRepBuilderAPI_Sewing &sewing, const TopoDS_Shape &shape) {
  sewing.Add(shape);
}
