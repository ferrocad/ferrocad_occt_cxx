#include <BRepPrimAPI_MakeBox.hxx>
#include <BRepPrimAPI_MakeCone.hxx>
#include <BRepPrimAPI_MakeCylinder.hxx>
#include <BRepPrimAPI_MakePrism.hxx>
#include <BRepPrimAPI_MakeRevol.hxx>
#include <BRepPrimAPI_MakeSphere.hxx>
#include <BRepPrimAPI_MakeTorus.hxx>
#include <Standard_Failure.hxx>
#include <bindings_common.hxx>
#include <stdexcept>

inline std::unique_ptr<BRepPrimAPI_MakeCylinder>
BRepPrimAPI_MakeCylinder_angle(const gp_Ax2 &coord_system, double radius, double height,
                               double angle) {
  try {
    return std::unique_ptr<BRepPrimAPI_MakeCylinder>(
        new BRepPrimAPI_MakeCylinder(coord_system, radius, height, angle));
  } catch (const Standard_Failure &e) {
    const char *msg = e.GetMessageString();
    throw std::runtime_error(msg ? msg : "OpenCASCADE Standard_Failure");
  }
}

inline std::unique_ptr<BRepPrimAPI_MakeSphere>
BRepPrimAPI_MakeSphere_full(const gp_Ax2 &axis, double r, double angle1, double angle2,
                            double angle3) {
  try {
    return std::unique_ptr<BRepPrimAPI_MakeSphere>(
        new BRepPrimAPI_MakeSphere(axis, r, angle1, angle2, angle3));
  } catch (const Standard_Failure &e) {
    const char *msg = e.GetMessageString();
    throw std::runtime_error(msg ? msg : "OpenCASCADE Standard_Failure");
  }
}
