#include <GeomConvert.hxx>
#include <Geom_BSplineCurve.hxx>
#include <Geom_Curve.hxx>
#include <Standard_Failure.hxx>
#include <bindings_common.hxx>
#include <stdexcept>

inline std::unique_ptr<Handle_Geom_BSplineCurve>
GeomConvert_CurveToBSplineCurve(const Handle_Geom_Curve &curve) {
  try {
    return std::unique_ptr<Handle_Geom_BSplineCurve>(
        new Handle_Geom_BSplineCurve(GeomConvert::CurveToBSplineCurve(curve)));
  } catch (const Standard_Failure &e) {
    const char *msg = e.GetMessageString();
    throw std::runtime_error(msg ? msg : "OpenCASCADE Standard_Failure");
  }
}
