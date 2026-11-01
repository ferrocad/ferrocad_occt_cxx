#include <BRepAdaptor_Curve.hxx>
#include <BRepAdaptor_Surface.hxx>
#include <bindings_common.hxx>
#include <gp_Pnt.hxx>
#include <gp_Vec.hxx>

inline std::unique_ptr<gp_Pnt> BRepAdaptor_Curve_value(const BRepAdaptor_Curve &curve, const Standard_Real U) {
  return std::unique_ptr<gp_Pnt>(new gp_Pnt(curve.Value(U)));
}

inline void BRepAdaptor_Curve_d1(const BRepAdaptor_Curve &curve, const Standard_Real u, gp_Pnt &point,
                                 gp_Vec &vec) {
  curve.D1(u, point, vec);
}

inline std::unique_ptr<gp_Pnt> BRepAdaptor_Surface_value(const BRepAdaptor_Surface &surface,
                                                         const Standard_Real u, const Standard_Real v) {
  return std::unique_ptr<gp_Pnt>(new gp_Pnt(surface.Value(u, v)));
}
