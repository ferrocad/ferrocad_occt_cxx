#include <GeomAbs_Shape.hxx>
#include <Geom_BSplineCurve.hxx>
#include <Geom_BSplineSurface.hxx>
#include <Geom_BezierCurve.hxx>
#include <Geom_BezierSurface.hxx>
#include <Geom_Circle.hxx>
#include <Geom_Conic.hxx>
#include <Geom_ConicalSurface.hxx>
#include <Geom_Curve.hxx>
#include <Geom_CylindricalSurface.hxx>
#include <Geom_Ellipse.hxx>
#include <Geom_Hyperbola.hxx>
#include <Geom_Line.hxx>
#include <Geom_OffsetCurve.hxx>
#include <Geom_Parabola.hxx>
#include <Geom_Plane.hxx>
#include <Geom_SphericalSurface.hxx>
#include <Geom_Surface.hxx>
#include <Geom_ToroidalSurface.hxx>
#include <Geom_TrimmedCurve.hxx>
#include <Standard_Failure.hxx>
#include <Standard_Type.hxx>
#include <TColgp_Array1OfPnt.hxx>
#include <TColgp_Array2OfPnt.hxx>
#include <TColStd_Array1OfInteger.hxx>
#include <TColStd_Array1OfReal.hxx>
#include <TColStd_Array2OfReal.hxx>
#include <bindings_common.hxx>
#include <gp_Ax2.hxx>
#include <gp_Ax3.hxx>
#include <gp_Circ.hxx>
#include <gp_Dir.hxx>
#include <gp_Elips.hxx>
#include <gp_Hypr.hxx>
#include <gp_Lin.hxx>
#include <gp_Parab.hxx>
#include <gp_Pln.hxx>
#include <gp_Pnt.hxx>
#include <stdexcept>

inline void geom_rethrow(const Standard_Failure &e) {
  const char *msg = e.GetMessageString();
  throw std::runtime_error(msg ? msg : "OpenCASCADE Standard_Failure");
}

// ---------------------------------------------------------------------------
// Curve construction
// ---------------------------------------------------------------------------

inline std::unique_ptr<Handle_Geom_Line> Geom_Line_new(const gp_Pnt &point, const gp_Dir &direction) {
  return std::unique_ptr<Handle_Geom_Line>(new Handle_Geom_Line(new Geom_Line(point, direction)));
}

inline std::unique_ptr<Handle_Geom_Circle> Geom_Circle_new(const gp_Ax2 &axis, double radius) {
  return std::unique_ptr<Handle_Geom_Circle>(new Handle_Geom_Circle(new Geom_Circle(axis, radius)));
}

inline std::unique_ptr<Handle_Geom_Ellipse> Geom_Ellipse_new(const gp_Ax2 &axis, double major_radius,
                                                             double minor_radius) {
  try {
    return std::unique_ptr<Handle_Geom_Ellipse>(
        new Handle_Geom_Ellipse(new Geom_Ellipse(axis, major_radius, minor_radius)));
  } catch (const Standard_Failure &e) {
    geom_rethrow(e);
    return nullptr;
  }
}

inline std::unique_ptr<Handle_Geom_Hyperbola> Geom_Hyperbola_new(const gp_Ax2 &axis,
                                                                 double major_radius,
                                                                 double minor_radius) {
  try {
    return std::unique_ptr<Handle_Geom_Hyperbola>(
        new Handle_Geom_Hyperbola(new Geom_Hyperbola(axis, major_radius, minor_radius)));
  } catch (const Standard_Failure &e) {
    geom_rethrow(e);
    return nullptr;
  }
}

inline std::unique_ptr<Handle_Geom_Parabola> Geom_Parabola_new(const gp_Ax2 &axis, double focal) {
  try {
    return std::unique_ptr<Handle_Geom_Parabola>(new Handle_Geom_Parabola(new Geom_Parabola(axis, focal)));
  } catch (const Standard_Failure &e) {
    geom_rethrow(e);
    return nullptr;
  }
}

inline std::unique_ptr<Handle_Geom_TrimmedCurve> Geom_TrimmedCurve_new(const Handle_Geom_Curve &curve,
                                                                       double u1, double u2) {
  try {
    return std::unique_ptr<Handle_Geom_TrimmedCurve>(
        new Handle_Geom_TrimmedCurve(new Geom_TrimmedCurve(curve, u1, u2)));
  } catch (const Standard_Failure &e) {
    geom_rethrow(e);
    return nullptr;
  }
}

inline std::unique_ptr<Handle_Geom_OffsetCurve> Geom_OffsetCurve_new(const Handle_Geom_Curve &curve,
                                                                     double offset,
                                                                     const gp_Dir &direction) {
  try {
    return std::unique_ptr<Handle_Geom_OffsetCurve>(
        new Handle_Geom_OffsetCurve(new Geom_OffsetCurve(curve, offset, direction)));
  } catch (const Standard_Failure &e) {
    geom_rethrow(e);
    return nullptr;
  }
}

inline std::unique_ptr<Handle_Geom_BezierCurve> Geom_BezierCurve_new(const TColgp_Array1OfPnt &poles) {
  try {
    return std::unique_ptr<Handle_Geom_BezierCurve>(
        new Handle_Geom_BezierCurve(new Geom_BezierCurve(poles)));
  } catch (const Standard_Failure &e) {
    geom_rethrow(e);
    return nullptr;
  }
}

inline std::unique_ptr<Handle_Geom_BezierCurve> Geom_BezierCurve_new_rational(
    const TColgp_Array1OfPnt &poles, const TColStd_Array1OfReal &weights) {
  try {
    return std::unique_ptr<Handle_Geom_BezierCurve>(
        new Handle_Geom_BezierCurve(new Geom_BezierCurve(poles, weights)));
  } catch (const Standard_Failure &e) {
    geom_rethrow(e);
    return nullptr;
  }
}

inline std::unique_ptr<Handle_Geom_BSplineCurve> Geom_BSplineCurve_new(
    const TColgp_Array1OfPnt &poles, const TColStd_Array1OfReal &knots,
    const TColStd_Array1OfInteger &multiplicities, int degree) {
  try {
    return std::unique_ptr<Handle_Geom_BSplineCurve>(
        new Handle_Geom_BSplineCurve(new Geom_BSplineCurve(poles, knots, multiplicities, degree)));
  } catch (const Standard_Failure &e) {
    geom_rethrow(e);
    return nullptr;
  }
}

inline std::unique_ptr<Handle_Geom_BSplineCurve>
Geom_BSplineCurve_new_full(const TColgp_Array1OfPnt &poles,
                           const TColStd_Array1OfReal &weights,
                           const TColStd_Array1OfReal &knots,
                           const TColStd_Array1OfInteger &multiplicities,
                           int degree, bool periodic, bool check_rational) {
  try {
    return std::unique_ptr<Handle_Geom_BSplineCurve>(new Handle_Geom_BSplineCurve(
        new Geom_BSplineCurve(poles, weights, knots, multiplicities, degree, periodic,
                              check_rational)));
  } catch (const Standard_Failure &e) {
    geom_rethrow(e);
    return nullptr;
  }
}

// ---------------------------------------------------------------------------
// Curve accessors
// ---------------------------------------------------------------------------

inline std::unique_ptr<gp_Lin> Geom_Line_Lin(const Handle_Geom_Line &line) {
  return std::unique_ptr<gp_Lin>(new gp_Lin(line->Lin()));
}

inline std::unique_ptr<gp_Circ> Geom_Circle_Circ(const Handle_Geom_Circle &circle) {
  return std::unique_ptr<gp_Circ>(new gp_Circ(circle->Circ()));
}

inline std::unique_ptr<gp_Elips> Geom_Ellipse_Elips(const Handle_Geom_Ellipse &ellipse) {
  return std::unique_ptr<gp_Elips>(new gp_Elips(ellipse->Elips()));
}

inline std::unique_ptr<gp_Hypr> Geom_Hyperbola_Hypr(const Handle_Geom_Hyperbola &hyperbola) {
  return std::unique_ptr<gp_Hypr>(new gp_Hypr(hyperbola->Hypr()));
}

inline std::unique_ptr<gp_Parab> Geom_Parabola_Parab(const Handle_Geom_Parabola &parabola) {
  return std::unique_ptr<gp_Parab>(new gp_Parab(parabola->Parab()));
}

inline const gp_Dir &Geom_OffsetCurve_Direction(const Handle_Geom_OffsetCurve &curve) {
  return curve->Direction();
}

inline double Geom_OffsetCurve_Offset(const Handle_Geom_OffsetCurve &curve) { return curve->Offset(); }

inline std::unique_ptr<Handle_Geom_Curve>
Geom_OffsetCurve_BasisCurve(const Handle_Geom_OffsetCurve &curve) {
  return std::unique_ptr<Handle_Geom_Curve>(new Handle_Geom_Curve(curve->BasisCurve()));
}

inline std::unique_ptr<Handle_Geom_Curve>
Geom_TrimmedCurve_BasisCurve(const Handle_Geom_TrimmedCurve &curve) {
  return std::unique_ptr<Handle_Geom_Curve>(new Handle_Geom_Curve(curve->BasisCurve()));
}

inline double HandleGeomCurve_FirstParameter(const Handle_Geom_Curve &curve) {
  return curve->FirstParameter();
}

inline double HandleGeomCurve_LastParameter(const Handle_Geom_Curve &curve) {
  return curve->LastParameter();
}

inline std::unique_ptr<Handle_Geom_Curve>
HandleGeomCurve_Transformed(const Handle_Geom_Curve &curve, const gp_Trsf &transform) {
  try {
    return std::unique_ptr<Handle_Geom_Curve>(
        new Handle_Geom_Curve(Handle(Geom_Curve)::DownCast(curve->Transformed(transform))));
  } catch (const Standard_Failure &e) {
    geom_rethrow(e);
    return nullptr;
  }
}

// ---------------------------------------------------------------------------
// B-spline curve accessors
// ---------------------------------------------------------------------------

inline int HandleGeomBSplineCurve_Degree(const Handle_Geom_BSplineCurve &curve) {
  return curve->Degree();
}

inline int HandleGeomBSplineCurve_MaxDegree() { return Geom_BSplineCurve::MaxDegree(); }

inline int HandleGeomBSplineCurve_NbPoles(const Handle_Geom_BSplineCurve &curve) {
  return curve->NbPoles();
}

inline int HandleGeomBSplineCurve_NbKnots(const Handle_Geom_BSplineCurve &curve) {
  return curve->NbKnots();
}

inline bool HandleGeomBSplineCurve_IsPeriodic(const Handle_Geom_BSplineCurve &curve) {
  return curve->IsPeriodic();
}

inline bool HandleGeomBSplineCurve_IsRational(const Handle_Geom_BSplineCurve &curve) {
  return curve->IsRational();
}

inline std::unique_ptr<gp_Pnt> HandleGeomBSplineCurve_StartPoint(const Handle_Geom_BSplineCurve &curve) {
  return std::unique_ptr<gp_Pnt>(new gp_Pnt(curve->StartPoint()));
}

inline std::unique_ptr<gp_Pnt> HandleGeomBSplineCurve_EndPoint(const Handle_Geom_BSplineCurve &curve) {
  return std::unique_ptr<gp_Pnt>(new gp_Pnt(curve->EndPoint()));
}

inline int HandleGeomBSplineCurve_FirstUKnotIndex(const Handle_Geom_BSplineCurve &curve) {
  return curve->FirstUKnotIndex();
}

inline int HandleGeomBSplineCurve_LastUKnotIndex(const Handle_Geom_BSplineCurve &curve) {
  return curve->LastUKnotIndex();
}

inline GeomAbs_Shape HandleGeomBSplineCurve_Continuity(const Handle_Geom_BSplineCurve &curve) {
  return curve->Continuity();
}

inline double HandleGeomBSplineCurve_Knot(const Handle_Geom_BSplineCurve &curve, int index) {
  return curve->Knot(index);
}

inline int HandleGeomBSplineCurve_Multiplicity(const Handle_Geom_BSplineCurve &curve, int index) {
  return curve->Multiplicity(index);
}

inline std::unique_ptr<gp_Pnt> HandleGeomBSplineCurve_Pole(const Handle_Geom_BSplineCurve &curve,
                                                           int index) {
  return std::unique_ptr<gp_Pnt>(new gp_Pnt(curve->Pole(index)));
}

inline double HandleGeomBSplineCurve_Weight(const Handle_Geom_BSplineCurve &curve, int index) {
  return curve->Weight(index);
}

inline std::unique_ptr<gp_Pnt> HandleGeomBSplineCurve_Value(const Handle_Geom_BSplineCurve &curve,
                                                            double u) {
  return std::unique_ptr<gp_Pnt>(new gp_Pnt(curve->Value(u)));
}

inline double HandleGeomBSplineCurve_Resolution(const Handle_Geom_BSplineCurve &curve,
                                                double tolerance3d) {
  double u_tolerance = 0.0;
  curve->Resolution(tolerance3d, u_tolerance);
  return u_tolerance;
}

inline void HandleGeomBSplineCurve_SetPeriodic(Handle_Geom_BSplineCurve &curve) {
  try {
    curve->SetPeriodic();
  } catch (const Standard_Failure &e) {
    geom_rethrow(e);
  }
}

inline void HandleGeomBSplineCurve_SetNotPeriodic(Handle_Geom_BSplineCurve &curve) {
  curve->SetNotPeriodic();
}

inline void HandleGeomBSplineCurve_Segment(Handle_Geom_BSplineCurve &curve, double u1, double u2) {
  try {
    curve->Segment(u1, u2);
  } catch (const Standard_Failure &e) {
    geom_rethrow(e);
  }
}

inline bool HandleGeomBSplineCurve_RemoveKnot(Handle_Geom_BSplineCurve &curve, int index, int m,
                                              double tolerance) {
  try {
    return curve->RemoveKnot(index, m, tolerance);
  } catch (const Standard_Failure &e) {
    geom_rethrow(e);
    return false;
  }
}

inline void HandleGeomBSplineCurve_InsertKnot(Handle_Geom_BSplineCurve &curve, double u, int m,
                                             double tolerance) {
  curve->InsertKnot(u, m, tolerance);
}

inline void HandleGeomBSplineCurve_SetKnots(Handle_Geom_BSplineCurve &curve,
                                            const TColStd_Array1OfReal &knots) {
  try {
    curve->SetKnots(knots);
  } catch (const Standard_Failure &e) {
    geom_rethrow(e);
  }
}

inline std::unique_ptr<TColStd_Array1OfReal>
HandleGeomBSplineCurve_KnotSequence(const Handle_Geom_BSplineCurve &curve) {
  try {
    Standard_Integer sequence_length = 0;
    if (curve->IsPeriodic()) {
      sequence_length = curve->NbPoles() + 2 * curve->Degree() - curve->Multiplicity(1) + 2;
    } else {
      for (Standard_Integer i = 1; i <= curve->NbKnots(); ++i) {
        sequence_length += curve->Multiplicity(i);
      }
    }
    std::unique_ptr<TColStd_Array1OfReal> sequence(
        new TColStd_Array1OfReal(1, sequence_length));
    curve->KnotSequence(*sequence);
    return sequence;
  } catch (const Standard_Failure &e) {
    geom_rethrow(e);
    return nullptr;
  }
}

inline std::unique_ptr<Handle_Geom_BSplineCurve>
HandleGeomBSplineCurve_Copy(const Handle_Geom_BSplineCurve &curve) {
  return std::unique_ptr<Handle_Geom_BSplineCurve>(
      new Handle_Geom_BSplineCurve(Handle(Geom_BSplineCurve)::DownCast(curve->Copy())));
}

// ---------------------------------------------------------------------------
// Bezier curve accessors
// ---------------------------------------------------------------------------

inline int HandleGeomBezierCurve_NbPoles(const Handle_Geom_BezierCurve &curve) {
  return curve->NbPoles();
}

inline std::unique_ptr<gp_Pnt> HandleGeomBezierCurve_Pole(const Handle_Geom_BezierCurve &curve,
                                                          int index) {
  return std::unique_ptr<gp_Pnt>(new gp_Pnt(curve->Pole(index)));
}

inline double HandleGeomBezierCurve_Weight(const Handle_Geom_BezierCurve &curve, int index) {
  return curve->Weight(index);
}

// ---------------------------------------------------------------------------
// Dynamic dispatch
// ---------------------------------------------------------------------------

inline bool GeomCurve_IsKind_line(const Handle_Geom_Curve &curve) {
  return !curve.IsNull() && curve->IsKind(STANDARD_TYPE(Geom_Line));
}

inline bool GeomCurve_IsKind_circle(const Handle_Geom_Curve &curve) {
  return !curve.IsNull() && curve->IsKind(STANDARD_TYPE(Geom_Circle));
}

inline bool GeomCurve_IsKind_ellipse(const Handle_Geom_Curve &curve) {
  return !curve.IsNull() && curve->IsKind(STANDARD_TYPE(Geom_Ellipse));
}

inline bool GeomCurve_IsKind_hyperbola(const Handle_Geom_Curve &curve) {
  return !curve.IsNull() && curve->IsKind(STANDARD_TYPE(Geom_Hyperbola));
}

inline bool GeomCurve_IsKind_parabola(const Handle_Geom_Curve &curve) {
  return !curve.IsNull() && curve->IsKind(STANDARD_TYPE(Geom_Parabola));
}

inline bool GeomCurve_IsKind_bezier(const Handle_Geom_Curve &curve) {
  return !curve.IsNull() && curve->IsKind(STANDARD_TYPE(Geom_BezierCurve));
}

inline bool GeomCurve_IsKind_bspline(const Handle_Geom_Curve &curve) {
  return !curve.IsNull() && curve->IsKind(STANDARD_TYPE(Geom_BSplineCurve));
}

inline bool GeomCurve_IsKind_offset(const Handle_Geom_Curve &curve) {
  return !curve.IsNull() && curve->IsKind(STANDARD_TYPE(Geom_OffsetCurve));
}

inline bool GeomCurve_IsKind_trimmed(const Handle_Geom_Curve &curve) {
  return !curve.IsNull() && curve->IsKind(STANDARD_TYPE(Geom_TrimmedCurve));
}

inline std::unique_ptr<Handle_Geom_Line> GeomCurve_DownCast_line(const Handle_Geom_Curve &curve) {
  return std::unique_ptr<Handle_Geom_Line>(new Handle_Geom_Line(opencascade::handle<Geom_Line>::DownCast(curve)));
}

inline std::unique_ptr<Handle_Geom_Circle> GeomCurve_DownCast_circle(const Handle_Geom_Curve &curve) {
  return std::unique_ptr<Handle_Geom_Circle>(new Handle_Geom_Circle(opencascade::handle<Geom_Circle>::DownCast(curve)));
}

inline std::unique_ptr<Handle_Geom_Ellipse> GeomCurve_DownCast_ellipse(const Handle_Geom_Curve &curve) {
  return std::unique_ptr<Handle_Geom_Ellipse>(
      new Handle_Geom_Ellipse(opencascade::handle<Geom_Ellipse>::DownCast(curve)));
}

inline std::unique_ptr<Handle_Geom_Hyperbola> GeomCurve_DownCast_hyperbola(const Handle_Geom_Curve &curve) {
  return std::unique_ptr<Handle_Geom_Hyperbola>(
      new Handle_Geom_Hyperbola(opencascade::handle<Geom_Hyperbola>::DownCast(curve)));
}

inline std::unique_ptr<Handle_Geom_Parabola> GeomCurve_DownCast_parabola(const Handle_Geom_Curve &curve) {
  return std::unique_ptr<Handle_Geom_Parabola>(
      new Handle_Geom_Parabola(opencascade::handle<Geom_Parabola>::DownCast(curve)));
}

inline std::unique_ptr<Handle_Geom_BezierCurve> GeomCurve_DownCast_bezier(const Handle_Geom_Curve &curve) {
  return std::unique_ptr<Handle_Geom_BezierCurve>(
      new Handle_Geom_BezierCurve(opencascade::handle<Geom_BezierCurve>::DownCast(curve)));
}

inline std::unique_ptr<Handle_Geom_BSplineCurve> GeomCurve_DownCast_bspline(const Handle_Geom_Curve &curve) {
  return std::unique_ptr<Handle_Geom_BSplineCurve>(
      new Handle_Geom_BSplineCurve(opencascade::handle<Geom_BSplineCurve>::DownCast(curve)));
}

inline std::unique_ptr<Handle_Geom_OffsetCurve> GeomCurve_DownCast_offset(const Handle_Geom_Curve &curve) {
  return std::unique_ptr<Handle_Geom_OffsetCurve>(
      new Handle_Geom_OffsetCurve(opencascade::handle<Geom_OffsetCurve>::DownCast(curve)));
}

inline std::unique_ptr<Handle_Geom_TrimmedCurve> GeomCurve_DownCast_trimmed(const Handle_Geom_Curve &curve) {
  return std::unique_ptr<Handle_Geom_TrimmedCurve>(
      new Handle_Geom_TrimmedCurve(opencascade::handle<Geom_TrimmedCurve>::DownCast(curve)));
}

// ---------------------------------------------------------------------------
// Surfaces
// ---------------------------------------------------------------------------

inline std::unique_ptr<Handle_Geom_ConicalSurface> Geom_ConicalSurface_new(const gp_Ax3 &axis,
                                                                           double angle,
                                                                           double radius) {
  try {
    return std::unique_ptr<Handle_Geom_ConicalSurface>(
        new Handle_Geom_ConicalSurface(new Geom_ConicalSurface(axis, angle, radius)));
  } catch (const Standard_Failure &e) {
    geom_rethrow(e);
    return nullptr;
  }
}

inline std::unique_ptr<Handle_Geom_SphericalSurface> Geom_SphericalSurface_new(const gp_Ax3 &axis,
                                                                               double radius) {
  try {
    return std::unique_ptr<Handle_Geom_SphericalSurface>(
        new Handle_Geom_SphericalSurface(new Geom_SphericalSurface(axis, radius)));
  } catch (const Standard_Failure &e) {
    geom_rethrow(e);
    return nullptr;
  }
}

inline std::unique_ptr<Handle_Geom_ToroidalSurface> Geom_ToroidalSurface_new(const gp_Ax3 &axis,
                                                                             double major_radius,
                                                                             double minor_radius) {
  try {
    return std::unique_ptr<Handle_Geom_ToroidalSurface>(
        new Handle_Geom_ToroidalSurface(new Geom_ToroidalSurface(axis, major_radius, minor_radius)));
  } catch (const Standard_Failure &e) {
    geom_rethrow(e);
    return nullptr;
  }
}

inline void Geom_Surface_Bounds(const Handle_Geom_Surface &surface, double &u1, double &u2,
                                double &v1, double &v2) {
  surface->Bounds(u1, u2, v1, v2);
}

inline std::unique_ptr<Handle_Geom_BSplineSurface> Geom_BSplineSurface_new(
    const TColgp_Array2OfPnt &poles, const TColStd_Array1OfReal &uknots,
    const TColStd_Array1OfReal &vknots, const TColStd_Array1OfInteger &umults,
    const TColStd_Array1OfInteger &vmults, int udegree, int vdegree) {
  try {
    return std::unique_ptr<Handle_Geom_BSplineSurface>(new Handle_Geom_BSplineSurface(
        new Geom_BSplineSurface(poles, uknots, vknots, umults, vmults, udegree, vdegree)));
  } catch (const Standard_Failure &e) {
    geom_rethrow(e);
    return nullptr;
  }
}

inline std::unique_ptr<Handle_Geom_BSplineSurface> Geom_BSplineSurface_new_full(
    const TColgp_Array2OfPnt &poles, const TColStd_Array2OfReal &weights,
    const TColStd_Array1OfReal &uknots, const TColStd_Array1OfReal &vknots,
    const TColStd_Array1OfInteger &umults, const TColStd_Array1OfInteger &vmults,
    int udegree, int vdegree, bool uperiodic, bool vperiodic) {
  try {
    return std::unique_ptr<Handle_Geom_BSplineSurface>(new Handle_Geom_BSplineSurface(
        new Geom_BSplineSurface(poles, weights, uknots, vknots, umults, vmults, udegree, vdegree,
                                uperiodic, vperiodic)));
  } catch (const Standard_Failure &e) {
    geom_rethrow(e);
    return nullptr;
  }
}

inline std::unique_ptr<gp_Pnt> HandleGeomBSplineSurface_Value(const Handle_Geom_BSplineSurface &surface,
                                                              double u, double v) {
  return std::unique_ptr<gp_Pnt>(new gp_Pnt(surface->Value(u, v)));
}

inline std::unique_ptr<gp_Pnt> HandleGeomBSplineSurface_Pole(const Handle_Geom_BSplineSurface &surface,
                                                             int u_index, int v_index) {
  return std::unique_ptr<gp_Pnt>(new gp_Pnt(surface->Pole(u_index, v_index)));
}

inline double HandleGeomBSplineSurface_Weight(const Handle_Geom_BSplineSurface &surface, int u_index,
                                              int v_index) {
  return surface->Weight(u_index, v_index);
}

inline int HandleGeomBSplineSurface_UDegree(const Handle_Geom_BSplineSurface &surface) {
  return surface->UDegree();
}

inline int HandleGeomBSplineSurface_VDegree(const Handle_Geom_BSplineSurface &surface) {
  return surface->VDegree();
}

inline int HandleGeomBSplineSurface_NbUPoles(const Handle_Geom_BSplineSurface &surface) {
  return surface->NbUPoles();
}

inline int HandleGeomBSplineSurface_NbVPoles(const Handle_Geom_BSplineSurface &surface) {
  return surface->NbVPoles();
}

inline int HandleGeomBSplineSurface_NbUKnots(const Handle_Geom_BSplineSurface &surface) {
  return surface->NbUKnots();
}

inline int HandleGeomBSplineSurface_NbVKnots(const Handle_Geom_BSplineSurface &surface) {
  return surface->NbVKnots();
}

inline bool HandleGeomBSplineSurface_IsUPeriodic(const Handle_Geom_BSplineSurface &surface) {
  return surface->IsUPeriodic();
}

inline bool HandleGeomBSplineSurface_IsVPeriodic(const Handle_Geom_BSplineSurface &surface) {
  return surface->IsVPeriodic();
}

inline double HandleGeomBSplineSurface_UKnot(const Handle_Geom_BSplineSurface &surface, int index) {
  return surface->UKnot(index);
}

inline double HandleGeomBSplineSurface_VKnot(const Handle_Geom_BSplineSurface &surface, int index) {
  return surface->VKnot(index);
}

inline int HandleGeomBSplineSurface_UMultiplicity(const Handle_Geom_BSplineSurface &surface,
                                                  int index) {
  return surface->UMultiplicity(index);
}

inline int HandleGeomBSplineSurface_VMultiplicity(const Handle_Geom_BSplineSurface &surface,
                                                  int index) {
  return surface->VMultiplicity(index);
}

inline void HandleGeomBSplineSurface_Bounds(const Handle_Geom_BSplineSurface &surface, double &u1,
                                            double &u2, double &v1, double &v2) {
  surface->Bounds(u1, u2, v1, v2);
}

inline const TColStd_Array1OfReal &
HandleGeomBSplineSurface_UKnotSequence(const Handle_Geom_BSplineSurface &surface) {
  return surface->UKnotSequence();
}

inline const TColStd_Array1OfReal &
HandleGeomBSplineSurface_VKnotSequence(const Handle_Geom_BSplineSurface &surface) {
  return surface->VKnotSequence();
}

inline std::unique_ptr<Handle_Geom_BSplineSurface>
downcast_to_bspline_surface(const Handle_Geom_Surface &surface) {
  return std::unique_ptr<Handle_Geom_BSplineSurface>(
      new Handle_Geom_BSplineSurface(opencascade::handle<Geom_BSplineSurface>::DownCast(surface)));
}

// ---------------------------------------------------------------------------
// Pre-existing helpers
// ---------------------------------------------------------------------------

inline std::unique_ptr<Handle_Geom_CylindricalSurface> Geom_CylindricalSurface_new(const gp_Ax3 &axis, double radius) {
  return std::unique_ptr<Handle_Geom_CylindricalSurface>(
      new Handle_Geom_CylindricalSurface(new Geom_CylindricalSurface(axis, radius)));
}

inline std::unique_ptr<Handle_Geom_Surface> cylinder_to_surface(const Handle_Geom_CylindricalSurface &cylinder_handle) {
  return std::unique_ptr<Handle_Geom_Surface>(new Handle_Geom_Surface(cylinder_handle));
}

inline std::unique_ptr<Handle_Geom_Surface> conical_to_surface(const Handle_Geom_ConicalSurface &conical_handle) {
  return std::unique_ptr<Handle_Geom_Surface>(new Handle_Geom_Surface(conical_handle));
}

inline std::unique_ptr<Handle_Geom_Surface> bspline_to_surface(const Handle_Geom_BSplineSurface &bspline_handle) {
  return std::unique_ptr<Handle_Geom_Surface>(new Handle_Geom_Surface(bspline_handle));
}

inline std::unique_ptr<Handle_Geom_Surface> spherical_to_surface(const Handle_Geom_SphericalSurface &spherical_handle) {
  return std::unique_ptr<Handle_Geom_Surface>(new Handle_Geom_Surface(spherical_handle));
}

inline std::unique_ptr<Handle_Geom_Surface> toroidal_to_surface(const Handle_Geom_ToroidalSurface &toroidal_handle) {
  return std::unique_ptr<Handle_Geom_Surface>(new Handle_Geom_Surface(toroidal_handle));
}

inline std::unique_ptr<Handle_Geom_BezierSurface> Geom_BezierSurface_new(const TColgp_Array2OfPnt &poles) {
  return std::unique_ptr<Handle_Geom_BezierSurface>(
      new Handle_Geom_BezierSurface(new Geom_BezierSurface(poles)));
}

inline const gp_Pnt &handle_geom_plane_location(const Handle_Geom_Plane &plane) { return plane->Location(); }

inline std::unique_ptr<gp_Pln> Handle_Geom_Plane_Pln(const Handle_Geom_Plane &plane) {
  return std::unique_ptr<gp_Pln>(new gp_Pln(plane->Pln()));
}

inline std::unique_ptr<Handle_Geom_BezierCurve>
Geom_BezierCurve_to_handle(std::unique_ptr<Geom_BezierCurve> bezier_curve) {
  return std::unique_ptr<Handle_Geom_BezierCurve>(new Handle_Geom_BezierCurve(bezier_curve.release()));
}

inline std::unique_ptr<Handle_Geom_Surface> bezier_to_surface(const Handle_Geom_BezierSurface &bezier_handle) {
  return std::unique_ptr<Handle_Geom_Surface>(new Handle_Geom_Surface(bezier_handle));
}

inline std::unique_ptr<Handle_Geom_Plane>
new_HandleGeomPlane_from_HandleGeomSurface(const Handle_Geom_Surface &surface) {
  Handle_Geom_Plane plane_handle = opencascade::handle<Geom_Plane>::DownCast(surface);
  return std::unique_ptr<Handle_Geom_Plane>(new Handle_Geom_Plane(plane_handle));
}

inline std::unique_ptr<Handle_Geom_Plane> Geom_Plane_new(const gp_Pln &plane) {
  return std::unique_ptr<Handle_Geom_Plane>(new Handle_Geom_Plane(new Geom_Plane(plane)));
}

inline std::unique_ptr<Handle_Geom_Surface> plane_to_surface(const Handle_Geom_Plane &plane_handle) {
  return std::unique_ptr<Handle_Geom_Surface>(new Handle_Geom_Surface(plane_handle));
}

inline std::unique_ptr<Handle_Geom_Surface> Handle_Geom_Surface_new() {
  return std::unique_ptr<Handle_Geom_Surface>(new Handle_Geom_Surface());
}

inline std::unique_ptr<gp_Pnt> HandleGeomCurve_Value(const Handle_Geom_Curve &curve, const Standard_Real U) {
  return std::unique_ptr<gp_Pnt>(new gp_Pnt(curve->Value(U)));
}

inline const Handle_Standard_Type &DynamicType(const Handle_Geom_Surface &surface) { return surface->DynamicType(); }
