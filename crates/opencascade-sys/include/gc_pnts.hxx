#include <BRepAdaptor_Curve.hxx>
#include <GCPnts_AbscissaPoint.hxx>
#include <GCPnts_TangentialDeflection.hxx>
#include <GCPnts_UniformAbscissa.hxx>
#include <GCPnts_UniformDeflection.hxx>
#include <Standard_Failure.hxx>
#include <bindings_common.hxx>
#include <gp_Pnt.hxx>
#include <stdexcept>

inline void gc_pnts_rethrow(const Standard_Failure &e) {
  const char *msg = e.GetMessageString();
  throw std::runtime_error(msg ? msg : "OpenCASCADE Standard_Failure");
}

inline std::unique_ptr<gp_Pnt> GCPnts_TangentialDeflection_Value(const GCPnts_TangentialDeflection &approximator,
                                                                 Standard_Integer i) {
  return std::unique_ptr<gp_Pnt>(new gp_Pnt(approximator.Value(i)));
}

inline std::unique_ptr<GCPnts_TangentialDeflection>
GCPnts_TangentialDeflection_new_range(const BRepAdaptor_Curve &curve, double first, double last,
                                      double angular_deflection, double curvature_deflection,
                                      int min_points) {
  try {
    return std::unique_ptr<GCPnts_TangentialDeflection>(new GCPnts_TangentialDeflection(
        curve, first, last, angular_deflection, curvature_deflection, min_points));
  } catch (const Standard_Failure &e) {
    gc_pnts_rethrow(e);
    return nullptr;
  }
}

inline void GCPnts_UniformAbscissa_Initialize_abscissa(GCPnts_UniformAbscissa &self,
                                                       const BRepAdaptor_Curve &curve,
                                                       double abscissa) {
  try {
    self.Initialize(curve, abscissa);
  } catch (const Standard_Failure &e) {
    gc_pnts_rethrow(e);
  }
}

inline void GCPnts_UniformAbscissa_Initialize_number(GCPnts_UniformAbscissa &self,
                                                     const BRepAdaptor_Curve &curve, int number,
                                                     double first, double last) {
  try {
    self.Initialize(curve, number, first, last);
  } catch (const Standard_Failure &e) {
    gc_pnts_rethrow(e);
  }
}

inline int GCPnts_UniformAbscissa_NbPoints(const GCPnts_UniformAbscissa &self) {
  try {
    return self.NbPoints();
  } catch (const Standard_Failure &e) {
    gc_pnts_rethrow(e);
    return 0;
  }
}

inline double GCPnts_UniformAbscissa_Parameter(const GCPnts_UniformAbscissa &self, int index) {
  try {
    return self.Parameter(index);
  } catch (const Standard_Failure &e) {
    gc_pnts_rethrow(e);
    return 0.0;
  }
}

inline std::unique_ptr<GCPnts_UniformDeflection>
GCPnts_UniformDeflection_new(const BRepAdaptor_Curve &curve, double deflection, double first,
                             double last) {
  try {
    return std::unique_ptr<GCPnts_UniformDeflection>(
        new GCPnts_UniformDeflection(curve, deflection, first, last));
  } catch (const Standard_Failure &e) {
    gc_pnts_rethrow(e);
    return nullptr;
  }
}

inline int GCPnts_UniformDeflection_NbPoints(const GCPnts_UniformDeflection &self) {
  try {
    return self.NbPoints();
  } catch (const Standard_Failure &e) {
    gc_pnts_rethrow(e);
    return 0;
  }
}

inline std::unique_ptr<gp_Pnt> GCPnts_UniformDeflection_Value(const GCPnts_UniformDeflection &self,
                                                              int index) {
  try {
    return std::unique_ptr<gp_Pnt>(new gp_Pnt(self.Value(index)));
  } catch (const Standard_Failure &e) {
    gc_pnts_rethrow(e);
    return nullptr;
  }
}

inline double GCPnts_AbscissaPoint_Length(const BRepAdaptor_Curve &curve, double tol) {
  try {
    return GCPnts_AbscissaPoint::Length(curve, tol);
  } catch (const Standard_Failure &e) {
    gc_pnts_rethrow(e);
    return 0.0;
  }
}

inline std::unique_ptr<GCPnts_AbscissaPoint>
GCPnts_AbscissaPoint_new(double tol, const BRepAdaptor_Curve &curve, double abscissa,
                         double first) {
  try {
    return std::unique_ptr<GCPnts_AbscissaPoint>(
        new GCPnts_AbscissaPoint(tol, curve, abscissa, first));
  } catch (const Standard_Failure &e) {
    gc_pnts_rethrow(e);
    return nullptr;
  }
}

inline double GCPnts_AbscissaPoint_Parameter(const GCPnts_AbscissaPoint &self) {
  try {
    return self.Parameter();
  } catch (const Standard_Failure &e) {
    gc_pnts_rethrow(e);
    return 0.0;
  }
}
