#include <BRepClass3d_SolidClassifier.hxx>
#include <BRepClass_FaceClassifier.hxx>
#include <Standard_Failure.hxx>
#include <TopAbs_State.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Shape.hxx>
#include <gp_Pnt.hxx>
#include <gp_Pnt2d.hxx>
#include <bindings_common.hxx>
#include <stdexcept>

struct SolidClassifierState {
  TopAbs_State state;
  bool on_face;
  TopAbs_State State() const { return state; }
  bool IsOnAFace() const { return on_face; }
};

inline void b_rep_class_rethrow(const Standard_Failure &e) {
  const char *msg = e.GetMessageString();
  throw std::runtime_error(msg ? msg : "OpenCASCADE Standard_Failure");
}

inline std::unique_ptr<SolidClassifierState>
BRepClass3d_SolidClassifier_Perform(const TopoDS_Shape &shape, double x, double y, double z,
                                    double tol) {
  try {
    BRepClass3d_SolidClassifier classifier(shape);
    classifier.Perform(gp_Pnt(x, y, z), tol);
    std::unique_ptr<SolidClassifierState> result(new SolidClassifierState);
    result->state = classifier.State();
    result->on_face = classifier.IsOnAFace();
    return result;
  } catch (const Standard_Failure &e) {
    b_rep_class_rethrow(e);
    return nullptr;
  }
}

inline TopAbs_State BRepClass_FaceClassifier_State(const TopoDS_Face &face, double u, double v,
                                                   double tol) {
  try {
    BRepClass_FaceClassifier classifier(face, gp_Pnt2d(u, v), tol);
    return classifier.State();
  } catch (const Standard_Failure &e) {
    b_rep_class_rethrow(e);
    return TopAbs_UNKNOWN;
  }
}
