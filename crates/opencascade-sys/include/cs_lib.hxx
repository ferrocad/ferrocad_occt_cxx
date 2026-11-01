#include <CSLib.hxx>
#include <CSLib_NormalStatus.hxx>
#include <Standard_Failure.hxx>
#include <gp_Dir.hxx>
#include <gp_Vec.hxx>
#include <bindings_common.hxx>
#include <stdexcept>

inline void cs_lib_rethrow(const Standard_Failure &e) {
  const char *msg = e.GetMessageString();
  throw std::runtime_error(msg ? msg : "OpenCASCADE Standard_Failure");
}

inline std::unique_ptr<gp_Dir> CSLib_Normal(const gp_Vec &d1u, const gp_Vec &d1v, const gp_Vec &d2u,
                                            const gp_Vec &d2v, const gp_Vec &duv, double tolerance,
                                            CSLib_NormalStatus &status) {
  try {
    Standard_Boolean done = false;
    gp_Dir normal;
    CSLib::Normal(d1u, d1v, d2u, d2v, duv, tolerance, done, status, normal);
    if (!done) {
      return nullptr;
    }
    return std::unique_ptr<gp_Dir>(new gp_Dir(normal));
  } catch (const Standard_Failure &e) {
    cs_lib_rethrow(e);
    return nullptr;
  }
}
