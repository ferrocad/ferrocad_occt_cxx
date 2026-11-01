#include <Geom2dConvert.hxx>
#include <Geom2d_BSplineCurve.hxx>
#include <Geom2d_Curve.hxx>
#include <Standard_Failure.hxx>
#include <bindings_common.hxx>
#include <stdexcept>

inline std::unique_ptr<Handle_Geom2d_Curve>
Geom2dConvert_CurveToBSplineCurve(const Handle_Geom2d_Curve &curve) {
  try {
    Handle(Geom2d_BSplineCurve) result = Geom2dConvert::CurveToBSplineCurve(curve);
    return std::unique_ptr<Handle_Geom2d_Curve>(new Handle_Geom2d_Curve(result));
  } catch (const Standard_Failure &e) {
    const char *msg = e.GetMessageString();
    throw std::runtime_error(msg ? msg : "OpenCASCADE Standard_Failure");
  }
}
