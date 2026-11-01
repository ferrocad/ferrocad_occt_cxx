#include <Geom2d_BSplineCurve.hxx>
#include <Geom2d_Ellipse.hxx>
#include <Geom2d_TrimmedCurve.hxx>
#include <Standard_Failure.hxx>
#include <TColgp_Array1OfPnt2d.hxx>
#include <TColStd_Array1OfInteger.hxx>
#include <TColStd_Array1OfReal.hxx>
#include <bindings_common.hxx>
#include <stdexcept>

inline void geom2d_rethrow(const Standard_Failure &e) {
  const char *msg = e.GetMessageString();
  throw std::runtime_error(msg ? msg : "OpenCASCADE Standard_Failure");
}

inline std::unique_ptr<Handle_Geom2d_Ellipse> Geom2d_Ellipse_new(const gp_Ax2d &axis, double major_radius,
                                                                 double minor_radius) {
  return std::unique_ptr<Handle_Geom2d_Ellipse>(
      new Handle_Geom2d_Ellipse(new Geom2d_Ellipse(axis, major_radius, minor_radius)));
}

inline std::unique_ptr<Handle_Geom2d_Curve> ellipse_to_HandleGeom2d_Curve(const Handle_Geom2d_Ellipse &ellipse_handle) {
  return std::unique_ptr<Handle_Geom2d_Curve>(new Handle_Geom2d_Curve(ellipse_handle));
}

inline std::unique_ptr<Handle_Geom2d_TrimmedCurve> Geom2d_TrimmedCurve_new(const Handle_Geom2d_Curve &curve, double u1,
                                                                           double u2) {
  return std::unique_ptr<Handle_Geom2d_TrimmedCurve>(
      new Handle_Geom2d_TrimmedCurve(new Geom2d_TrimmedCurve(curve, u1, u2)));
}

inline std::unique_ptr<Handle_Geom2d_Curve>
HandleGeom2d_TrimmedCurve_to_curve(const Handle_Geom2d_TrimmedCurve &trimmed_curve) {
  return std::unique_ptr<Handle_Geom2d_Curve>(new Handle_Geom2d_Curve(trimmed_curve));
}

inline std::unique_ptr<gp_Pnt2d> ellipse_value(const Handle_Geom2d_Ellipse &ellipse, double u) {
  return std::unique_ptr<gp_Pnt2d>(new gp_Pnt2d(ellipse->Value(u)));
}

inline std::unique_ptr<Handle_Geom2d_BSplineCurve> Geom2d_BSplineCurve_new(
    const TColgp_Array1OfPnt2d &poles, const TColStd_Array1OfReal &knots,
    const TColStd_Array1OfInteger &multiplicities, int degree) {
  try {
    return std::unique_ptr<Handle_Geom2d_BSplineCurve>(
        new Handle_Geom2d_BSplineCurve(new Geom2d_BSplineCurve(poles, knots, multiplicities, degree)));
  } catch (const Standard_Failure &e) {
    geom2d_rethrow(e);
    return nullptr;
  }
}

inline const TColgp_Array1OfPnt2d &Geom2d_BSplineCurve_Poles(const Handle_Geom2d_BSplineCurve &curve) {
  return curve->Poles();
}

inline int Geom2d_BSplineCurve_Degree(const Handle_Geom2d_BSplineCurve &curve) {
  return curve->Degree();
}

inline bool Geom2d_BSplineCurve_IsPeriodic(const Handle_Geom2d_BSplineCurve &curve) {
  return curve->IsPeriodic();
}
