#include <GeomAdaptor_Curve.hxx>
#include <GeomAdaptor_Surface.hxx>
#include <Geom_Curve.hxx>
#include <Geom_Surface.hxx>
#include <Standard_Failure.hxx>
#include <gp_Pln.hxx>
#include <bindings_common.hxx>
#include <stdexcept>

inline void geom_adaptor_rethrow(const Standard_Failure &e) {
  const char *msg = e.GetMessageString();
  throw std::runtime_error(msg ? msg : "OpenCASCADE Standard_Failure");
}

inline std::unique_ptr<GeomAdaptor_Surface>
GeomAdaptor_Surface_new(const Handle_Geom_Surface &surface) {
  try {
    return std::unique_ptr<GeomAdaptor_Surface>(new GeomAdaptor_Surface(surface));
  } catch (const Standard_Failure &e) {
    geom_adaptor_rethrow(e);
    return nullptr;
  }
}

inline std::unique_ptr<gp_Pln> GeomAdaptor_Surface_Plane(const GeomAdaptor_Surface &adaptor) {
  try {
    return std::unique_ptr<gp_Pln>(new gp_Pln(adaptor.Plane()));
  } catch (const Standard_Failure &e) {
    geom_adaptor_rethrow(e);
    return nullptr;
  }
}

inline std::unique_ptr<Handle_Geom_Curve> GeomAdaptor_Curve_Curve(const GeomAdaptor_Curve &adaptor) {
  return std::unique_ptr<Handle_Geom_Curve>(new Handle_Geom_Curve(adaptor.Curve()));
}
