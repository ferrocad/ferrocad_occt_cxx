#include <BRepTopAdaptor_FClass2d.hxx>
#include <Precision.hxx>
#include <Standard_Failure.hxx>
#include <TopAbs_State.hxx>
#include <TopoDS_Face.hxx>
#include <gp_Pnt2d.hxx>
#include <bindings_common.hxx>
#include <stdexcept>

inline TopAbs_State BRepTopAdaptor_FClass2d_Perform(const TopoDS_Face &face, double u, double v) {
  try {
    BRepTopAdaptor_FClass2d classifier(face, Precision::Confusion());
    return classifier.Perform(gp_Pnt2d(u, v));
  } catch (const Standard_Failure &e) {
    const char *msg = e.GetMessageString();
    throw std::runtime_error(msg ? msg : "OpenCASCADE Standard_Failure");
  }
}
