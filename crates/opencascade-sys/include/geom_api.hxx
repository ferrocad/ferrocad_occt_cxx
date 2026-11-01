#include <GeomAPI.hxx>
#include <GeomAPI_Interpolate.hxx>
#include <GeomAPI_PointsToBSpline.hxx>
#include <GeomAPI_PointsToBSplineSurface.hxx>
#include <GeomAPI_ProjectPointOnCurve.hxx>
#include <GeomAPI_ProjectPointOnSurf.hxx>
#include <Geom2dAPI_InterCurveCurve.hxx>
#include <Geom2dAPI_ProjectPointOnCurve.hxx>
#include <Geom2d_Curve.hxx>
#include <gp_Pnt2d.hxx>
#include <GeomAbs_Shape.hxx>
#include <Geom_BSplineCurve.hxx>
#include <Geom_BSplineSurface.hxx>
#include <Geom_Curve.hxx>
#include <Geom_Surface.hxx>
#include <Standard_Failure.hxx>
#include <TColgp_Array1OfPnt.hxx>
#include <gp_Pln.hxx>
#include <gp_Pnt.hxx>
#include <bindings_common.hxx>
#include <stdexcept>

inline void geom_api_rethrow(const Standard_Failure &e) {
  const char *msg = e.GetMessageString();
  throw std::runtime_error(msg ? msg : "OpenCASCADE Standard_Failure");
}

inline std::unique_ptr<Handle_Geom_BSplineCurve> GeomAPI_Interpolate_Curve(const GeomAPI_Interpolate &interpolate) {
  return std::unique_ptr<Handle_Geom_BSplineCurve>(new Handle_Geom_BSplineCurve(interpolate.Curve()));
}

inline std::unique_ptr<GeomAPI_PointsToBSpline>
GeomAPI_PointsToBSpline_new(rust::Slice<const double> points, int deg_min, int deg_max,
                            GeomAbs_Shape continuity, double tol) {
  const int count = static_cast<int>(points.size() / 3);
  if (points.size() % 3 != 0 || count < 2) {
    throw std::runtime_error("GeomAPI_PointsToBSpline_new: points must be >= 2 xyz triplets");
  }
  try {
    TColgp_Array1OfPnt pts(1, count);
    for (int i = 0; i < count; ++i) {
      pts.SetValue(i + 1, gp_Pnt(points[3 * i], points[3 * i + 1], points[3 * i + 2]));
    }
    return std::unique_ptr<GeomAPI_PointsToBSpline>(
        new GeomAPI_PointsToBSpline(pts, deg_min, deg_max, continuity, tol));
  } catch (const Standard_Failure &e) {
    geom_api_rethrow(e);
    return nullptr;
  }
}

inline std::unique_ptr<Handle_Geom_BSplineCurve>
GeomAPI_PointsToBSpline_Curve(const GeomAPI_PointsToBSpline &approx) {
  return std::unique_ptr<Handle_Geom_BSplineCurve>(new Handle_Geom_BSplineCurve(approx.Curve()));
}

inline std::unique_ptr<GeomAPI_ProjectPointOnCurve>
GeomAPI_ProjectPointOnCurve_new(const gp_Pnt &point, const Handle_Geom_Curve &curve) {
  try {
    return std::unique_ptr<GeomAPI_ProjectPointOnCurve>(
        new GeomAPI_ProjectPointOnCurve(point, curve));
  } catch (const Standard_Failure &e) {
    geom_api_rethrow(e);
    return nullptr;
  }
}

inline double GeomAPI_ProjectPointOnCurve_Parameter(const GeomAPI_ProjectPointOnCurve &curve,
                                                    int index) {
  try {
    return curve.Parameter(index);
  } catch (const Standard_Failure &e) {
    geom_api_rethrow(e);
    return 0.0;
  }
}

inline std::unique_ptr<Handle_Geom2d_Curve> GeomAPI_To2d(const Handle_Geom_Curve &curve,
                                                         const gp_Pln &plane) {
  try {
    Handle(Geom2d_Curve) result = GeomAPI::To2d(curve, plane);
    return std::unique_ptr<Handle_Geom2d_Curve>(new Handle_Geom2d_Curve(result));
  } catch (const Standard_Failure &e) {
    geom_api_rethrow(e);
    return nullptr;
  }
}

inline void GeomAPI_PointsToBSplineSurface_Interpolate(GeomAPI_PointsToBSplineSurface &approx,
                                                       const TColgp_Array2OfPnt &points,
                                                       bool periodic) {
  try {
    approx.Interpolate(points, periodic);
  } catch (const Standard_Failure &e) {
    geom_api_rethrow(e);
  }
}

inline std::unique_ptr<Handle_Geom_Surface>
GeomAPI_PointsToBSplineSurface_Surface(const GeomAPI_PointsToBSplineSurface &approx) {
  return std::unique_ptr<Handle_Geom_Surface>(new Handle_Geom_Surface(approx.Surface()));
}

inline std::unique_ptr<Geom2dAPI_InterCurveCurve>
Geom2dAPI_InterCurveCurve_new(const Handle_Geom2d_Curve &curve, double tol) {
  try {
    return std::unique_ptr<Geom2dAPI_InterCurveCurve>(
        new Geom2dAPI_InterCurveCurve(curve, tol));
  } catch (const Standard_Failure &e) {
    geom_api_rethrow(e);
    return nullptr;
  }
}

inline std::unique_ptr<gp_Pnt2d> Geom2dAPI_InterCurveCurve_Point(
    const Geom2dAPI_InterCurveCurve &curve, int index) {
  try {
    return std::unique_ptr<gp_Pnt2d>(new gp_Pnt2d(curve.Point(index)));
  } catch (const Standard_Failure &e) {
    geom_api_rethrow(e);
    return nullptr;
  }
}

inline std::unique_ptr<Geom2dAPI_ProjectPointOnCurve>
Geom2dAPI_ProjectPointOnCurve_new(const gp_Pnt2d &point, const Handle_Geom2d_Curve &curve,
                                  double first, double last) {
  try {
    return std::unique_ptr<Geom2dAPI_ProjectPointOnCurve>(
        new Geom2dAPI_ProjectPointOnCurve(point, curve, first, last));
  } catch (const Standard_Failure &e) {
    geom_api_rethrow(e);
    return nullptr;
  }
}

inline double Geom2dAPI_ProjectPointOnCurve_Parameter(
    const Geom2dAPI_ProjectPointOnCurve &curve, int index) {
  try {
    return curve.Parameter(index);
  } catch (const Standard_Failure &e) {
    geom_api_rethrow(e);
    return 0.0;
  }
}
