#include <BRepExtrema_DistShapeShape.hxx>
#include <bindings_common.hxx>
#include <gp_Pnt.hxx>

inline std::unique_ptr<gp_Pnt> BRepExtrema_DistShapeShape_point_on_shape1(const BRepExtrema_DistShapeShape &d,
                                                                          Standard_Integer index) {
  return std::unique_ptr<gp_Pnt>(new gp_Pnt(d.PointOnShape1(index)));
}

inline std::unique_ptr<gp_Pnt> BRepExtrema_DistShapeShape_point_on_shape2(const BRepExtrema_DistShapeShape &d,
                                                                          Standard_Integer index) {
  return std::unique_ptr<gp_Pnt>(new gp_Pnt(d.PointOnShape2(index)));
}
