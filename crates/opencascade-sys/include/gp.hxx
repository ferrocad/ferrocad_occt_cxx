#include <bindings_common.hxx>
#include <gp.hxx>
#include <gp_Ax1.hxx>
#include <gp_Ax2.hxx>
#include <gp_Ax3.hxx>
#include <gp_Circ.hxx>
#include <gp_Cone.hxx>
#include <gp_Cylinder.hxx>
#include <gp_Dir.hxx>
#include <gp_Elips.hxx>
#include <gp_GTrsf.hxx>
#include <gp_Hypr.hxx>
#include <gp_Lin.hxx>
#include <gp_Mat.hxx>
#include <gp_Parab.hxx>
#include <gp_Pln.hxx>
#include <gp_Pnt.hxx>
#include <gp_Sphere.hxx>
#include <gp_Torus.hxx>
#include <gp_Trsf.hxx>
#include <gp_Vec.hxx>
#include <Standard_Failure.hxx>
#include <stdexcept>

inline void gp_rethrow(const Standard_Failure &e) {
  const char *msg = e.GetMessageString();
  throw std::runtime_error(msg ? msg : "OpenCASCADE Standard_Failure");
}

inline std::unique_ptr<gp_Elips> gp_Elips_new(const gp_Ax2 &axis, double major_radius,
                                              double minor_radius) {
  try {
    return std::unique_ptr<gp_Elips>(new gp_Elips(axis, major_radius, minor_radius));
  } catch (const Standard_Failure &e) {
    gp_rethrow(e);
    return nullptr;
  }
}

inline std::unique_ptr<gp_Hypr> gp_Hypr_new(const gp_Ax2 &axis, double major_radius,
                                            double minor_radius) {
  try {
    return std::unique_ptr<gp_Hypr>(new gp_Hypr(axis, major_radius, minor_radius));
  } catch (const Standard_Failure &e) {
    gp_rethrow(e);
    return nullptr;
  }
}

inline std::unique_ptr<gp_Parab> gp_Parab_new(const gp_Ax2 &axis, double focal) {
  try {
    return std::unique_ptr<gp_Parab>(new gp_Parab(axis, focal));
  } catch (const Standard_Failure &e) {
    gp_rethrow(e);
    return nullptr;
  }
}

inline std::unique_ptr<gp_Pln> gp_Pln_new_abcd(double a, double b, double c, double d) {
  try {
    return std::unique_ptr<gp_Pln>(new gp_Pln(a, b, c, d));
  } catch (const Standard_Failure &e) {
    gp_rethrow(e);
    return nullptr;
  }
}

inline std::unique_ptr<gp_Pln> gp_Pln_new_frame(const gp_Ax3 &frame) {
  try {
    return std::unique_ptr<gp_Pln>(new gp_Pln(frame));
  } catch (const Standard_Failure &e) {
    gp_rethrow(e);
    return nullptr;
  }
}

inline std::unique_ptr<gp_Ax2> gp_Ax2_new3(const gp_Pnt &origin, const gp_Dir &main_dir,
                                           const gp_Dir &x_dir) {
  try {
    return std::unique_ptr<gp_Ax2>(new gp_Ax2(origin, main_dir, x_dir));
  } catch (const Standard_Failure &e) {
    gp_rethrow(e);
    return nullptr;
  }
}

inline std::unique_ptr<gp_Ax3> gp_Ax3_new3(const gp_Pnt &origin, const gp_Dir &main_dir,
                                           const gp_Dir &x_dir) {
  try {
    return std::unique_ptr<gp_Ax3>(new gp_Ax3(origin, main_dir, x_dir));
  } catch (const Standard_Failure &e) {
    gp_rethrow(e);
    return nullptr;
  }
}

inline double gp_Mat_Value(const gp_Mat &matrix, int row, int col) {
  return matrix.Value(row, col);
}

inline std::unique_ptr<gp_Vec> gp_Vec_Crossed(const gp_Vec &left, const gp_Vec &right) {
  return std::unique_ptr<gp_Vec>(new gp_Vec(left.Crossed(right)));
}

inline void gp_Trsf_SetValues(gp_Trsf &transform, double a11, double a12, double a13, double a14,
                              double a21, double a22, double a23, double a24, double a31, double a32,
                              double a33, double a34) {
  try {
    transform.SetValues(a11, a12, a13, a14, a21, a22, a23, a24, a31, a32, a33, a34);
  } catch (const Standard_Failure &e) {
    gp_rethrow(e);
  }
}

inline std::unique_ptr<gp_Cylinder> gp_Cylinder_new(const gp_Ax3 &axis, double radius) {
  try {
    return std::unique_ptr<gp_Cylinder>(new gp_Cylinder(axis, radius));
  } catch (const Standard_Failure &e) {
    gp_rethrow(e);
    return nullptr;
  }
}

inline std::unique_ptr<gp_Sphere> gp_Sphere_new(const gp_Ax3 &axis, double radius) {
  try {
    return std::unique_ptr<gp_Sphere>(new gp_Sphere(axis, radius));
  } catch (const Standard_Failure &e) {
    gp_rethrow(e);
    return nullptr;
  }
}

inline std::unique_ptr<gp_Cone> gp_Cone_new(const gp_Ax3 &axis, double semi_angle, double radius) {
  try {
    return std::unique_ptr<gp_Cone>(new gp_Cone(axis, semi_angle, radius));
  } catch (const Standard_Failure &e) {
    gp_rethrow(e);
    return nullptr;
  }
}

inline std::unique_ptr<gp_Torus> gp_Torus_new(const gp_Ax3 &axis, double major_radius,
                                              double minor_radius) {
  try {
    return std::unique_ptr<gp_Torus>(new gp_Torus(axis, major_radius, minor_radius));
  } catch (const Standard_Failure &e) {
    gp_rethrow(e);
    return nullptr;
  }
}

inline std::unique_ptr<gp_Ax1> gp_Pln_Axis(const gp_Pln &plane) {
  return std::unique_ptr<gp_Ax1>(new gp_Ax1(plane.Axis()));
}

inline std::unique_ptr<gp_Dir> gp_Ax1_Direction(const gp_Ax1 &axis) {
  return std::unique_ptr<gp_Dir>(new gp_Dir(axis.Direction()));
}

inline std::unique_ptr<gp_Dir> gp_Dir_Reversed(const gp_Dir &dir) {
  return std::unique_ptr<gp_Dir>(new gp_Dir(dir.Reversed()));
}

inline std::unique_ptr<gp_Ax3> gp_Pln_Position(const gp_Pln &plane) {
  return std::unique_ptr<gp_Ax3>(new gp_Ax3(plane.Position()));
}

inline std::unique_ptr<gp_Ax3> gp_Cylinder_Position(const gp_Cylinder &cylinder) {
  return std::unique_ptr<gp_Ax3>(new gp_Ax3(cylinder.Position()));
}

inline std::unique_ptr<gp_Ax3> gp_Sphere_Position(const gp_Sphere &sphere) {
  return std::unique_ptr<gp_Ax3>(new gp_Ax3(sphere.Position()));
}

inline std::unique_ptr<gp_Ax3> gp_Cone_Position(const gp_Cone &cone) {
  return std::unique_ptr<gp_Ax3>(new gp_Ax3(cone.Position()));
}

inline std::unique_ptr<gp_Ax3> gp_Torus_Position(const gp_Torus &torus) {
  return std::unique_ptr<gp_Ax3>(new gp_Ax3(torus.Position()));
}
