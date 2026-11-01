#include <BRepAdaptor_CompCurve.hxx>
#include <BRepAdaptor_Curve.hxx>
#include <BRepAdaptor_Surface.hxx>
#include <GeomAdaptor_Curve.hxx>
#include <Standard_Failure.hxx>
#include <bindings_common.hxx>
#include <gp_Cone.hxx>
#include <gp_Cylinder.hxx>
#include <gp_Pln.hxx>
#include <gp_Pnt.hxx>
#include <gp_Sphere.hxx>
#include <gp_Torus.hxx>
#include <gp_Vec.hxx>

#include <stdexcept>

inline std::unique_ptr<gp_Pnt> BRepAdaptor_Curve_value(const BRepAdaptor_Curve &curve, const Standard_Real U) {
  return std::unique_ptr<gp_Pnt>(new gp_Pnt(curve.Value(U)));
}

inline void BRepAdaptor_Curve_d1(const BRepAdaptor_Curve &curve, const Standard_Real u, gp_Pnt &point,
                                 gp_Vec &vec) {
  curve.D1(u, point, vec);
}

inline const GeomAdaptor_Curve &BRepAdaptor_Curve_Curve(const BRepAdaptor_Curve &curve) {
  return curve.Curve();
}

inline std::unique_ptr<gp_Pnt> BRepAdaptor_Surface_value(const BRepAdaptor_Surface &surface,
                                                         const Standard_Real u, const Standard_Real v) {
  return std::unique_ptr<gp_Pnt>(new gp_Pnt(surface.Value(u, v)));
}

inline void b_rep_adaptor_rethrow(const Standard_Failure &e) {
  const char *msg = e.GetMessageString();
  throw std::runtime_error(msg ? msg : "OpenCASCADE Standard_Failure");
}

inline std::unique_ptr<gp_Pln> BRepAdaptor_Surface_Plane(const BRepAdaptor_Surface &surface) {
  try {
    return std::unique_ptr<gp_Pln>(new gp_Pln(surface.Plane()));
  } catch (const Standard_Failure &e) {
    b_rep_adaptor_rethrow(e);
    return nullptr;
  }
}

inline GeomAbs_SurfaceType BRepAdaptor_Surface_GetType(const BRepAdaptor_Surface &surface) {
  return surface.GetType();
}

inline std::unique_ptr<gp_Cylinder> BRepAdaptor_Surface_Cylinder(const BRepAdaptor_Surface &surface) {
  try {
    return std::unique_ptr<gp_Cylinder>(new gp_Cylinder(surface.Cylinder()));
  } catch (const Standard_Failure &e) {
    b_rep_adaptor_rethrow(e);
    return nullptr;
  }
}

inline std::unique_ptr<gp_Sphere> BRepAdaptor_Surface_Sphere(const BRepAdaptor_Surface &surface) {
  try {
    return std::unique_ptr<gp_Sphere>(new gp_Sphere(surface.Sphere()));
  } catch (const Standard_Failure &e) {
    b_rep_adaptor_rethrow(e);
    return nullptr;
  }
}

inline std::unique_ptr<gp_Cone> BRepAdaptor_Surface_Cone(const BRepAdaptor_Surface &surface) {
  try {
    return std::unique_ptr<gp_Cone>(new gp_Cone(surface.Cone()));
  } catch (const Standard_Failure &e) {
    b_rep_adaptor_rethrow(e);
    return nullptr;
  }
}

inline std::unique_ptr<gp_Torus> BRepAdaptor_Surface_Torus(const BRepAdaptor_Surface &surface) {
  try {
    return std::unique_ptr<gp_Torus>(new gp_Torus(surface.Torus()));
  } catch (const Standard_Failure &e) {
    b_rep_adaptor_rethrow(e);
    return nullptr;
  }
}

inline std::unique_ptr<gp_Pnt> BRepAdaptor_CompCurve_value(const BRepAdaptor_CompCurve &curve,
                                                           const Standard_Real u) {
  return std::unique_ptr<gp_Pnt>(new gp_Pnt(curve.Value(u)));
}

inline void BRepAdaptor_CompCurve_d1(const BRepAdaptor_CompCurve &curve, const Standard_Real u,
                                     gp_Pnt &point, gp_Vec &vec) {
  curve.D1(u, point, vec);
}
