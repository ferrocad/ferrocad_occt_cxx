#include <BSplCLib.hxx>
#include <TColStd_Array1OfReal.hxx>
#include <Standard_Failure.hxx>
#include <bindings_common.hxx>
#include <stdexcept>

inline void BSplCLib_Reparametrize(double first, double last, TColStd_Array1OfReal &knots) {
  try {
    BSplCLib::Reparametrize(first, last, knots);
  } catch (const Standard_Failure &e) {
    const char *msg = e.GetMessageString();
    throw std::runtime_error(msg ? msg : "OpenCASCADE Standard_Failure");
  }
}
