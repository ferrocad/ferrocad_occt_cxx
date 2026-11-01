#include <ShapeConstruct_Curve.hxx>
#include <Geom_BSplineCurve.hxx>
#include <Geom_Curve.hxx>
#include <Standard_Failure.hxx>
#include <bindings_common.hxx>
#include <stdexcept>

inline std::unique_ptr<Handle_Geom_BSplineCurve>
ShapeConstruct_Curve_ConvertToBSpline(const ShapeConstruct_Curve &self, const Handle_Geom_Curve &source,
                                      double first, double last, double precision) {
  try {
    return std::unique_ptr<Handle_Geom_BSplineCurve>(
        new Handle_Geom_BSplineCurve(self.ConvertToBSpline(source, first, last, precision)));
  } catch (const Standard_Failure &e) {
    const char *msg = e.GetMessageString();
    throw std::runtime_error(msg ? msg : "OpenCASCADE Standard_Failure");
  }
}
