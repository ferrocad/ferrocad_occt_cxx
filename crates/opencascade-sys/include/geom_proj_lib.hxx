#include <GeomProjLib.hxx>
#include <Geom2d_Curve.hxx>
#include <Geom_Curve.hxx>
#include <Geom_Surface.hxx>
#include <Standard_Failure.hxx>
#include <bindings_common.hxx>
#include <stdexcept>

inline std::unique_ptr<Handle_Geom2d_Curve>
GeomProjLib_Curve2d(const Handle_Geom_Curve &curve, double first, double last,
                    const Handle_Geom_Surface &surface) {
  try {
    Handle(Geom2d_Curve) result = GeomProjLib::Curve2d(curve, first, last, surface);
    return std::unique_ptr<Handle_Geom2d_Curve>(new Handle_Geom2d_Curve(result));
  } catch (const Standard_Failure &e) {
    const char *msg = e.GetMessageString();
    throw std::runtime_error(msg ? msg : "OpenCASCADE Standard_Failure");
  }
}
