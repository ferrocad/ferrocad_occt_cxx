#include <BRepAlgoAPI_BuilderAlgo.hxx>
#include <BRepAlgoAPI_Common.hxx>
#include <BRepAlgoAPI_Cut.hxx>
#include <BRepAlgoAPI_Defeaturing.hxx>
#include <BRepAlgoAPI_Fuse.hxx>
#include <BRepAlgoAPI_Section.hxx>
#include <Standard_Failure.hxx>
#include <TopoDS_Shape.hxx>
#include <bindings_common.hxx>
#include <stdexcept>

inline void b_rep_algo_api_rethrow(const Standard_Failure &e) {
  const char *msg = e.GetMessageString();
  throw std::runtime_error(msg ? msg : "OpenCASCADE Standard_Failure");
}

inline std::unique_ptr<BRepAlgoAPI_Defeaturing> BRepAlgoAPI_Defeaturing_new() {
  return std::unique_ptr<BRepAlgoAPI_Defeaturing>(new BRepAlgoAPI_Defeaturing());
}

inline void BRepAlgoAPI_Defeaturing_SetRunParallel(BRepAlgoAPI_Defeaturing &d, bool enabled) {
  d.SetRunParallel(enabled);
}

inline void BRepAlgoAPI_Defeaturing_SetToFillHistory(BRepAlgoAPI_Defeaturing &d, bool enabled) {
  d.SetToFillHistory(enabled);
}

inline void BRepAlgoAPI_Defeaturing_SetShape(BRepAlgoAPI_Defeaturing &d, const TopoDS_Shape &shape) {
  d.SetShape(shape);
}

inline void BRepAlgoAPI_Defeaturing_AddFaceToRemove(BRepAlgoAPI_Defeaturing &d, const TopoDS_Shape &shape) {
  d.AddFaceToRemove(shape);
}

inline void BRepAlgoAPI_Defeaturing_Build(BRepAlgoAPI_Defeaturing &d) {
  try {
    d.Build();
  } catch (const Standard_Failure &e) {
    b_rep_algo_api_rethrow(e);
  }
}

inline bool BRepAlgoAPI_Defeaturing_IsDone(const BRepAlgoAPI_Defeaturing &d) {
  return d.IsDone();
}

inline std::unique_ptr<TopoDS_Shape> BRepAlgoAPI_Defeaturing_Shape(BRepAlgoAPI_Defeaturing &d) {
  try {
    return std::unique_ptr<TopoDS_Shape>(new TopoDS_Shape(d.Shape()));
  } catch (const Standard_Failure &e) {
    b_rep_algo_api_rethrow(e);
    return nullptr;
  }
}

// `BOPAlgo_Options` is a protected base of `BRepAlgoAPI_Cut`. A caller can still
// invoke its public setters through the derived object, but cxx's direct method
// bindings take a pointer to the inherited member, which needs an inaccessible
// base-to-derived conversion. These helpers keep the same call reachable.
inline void BRepAlgoAPI_Cut_SetRunParallel(BRepAlgoAPI_Cut &op, bool enabled) {
  op.SetRunParallel(enabled);
}

inline void BRepAlgoAPI_Cut_SetFuzzyValue(BRepAlgoAPI_Cut &op, double value) {
  op.SetFuzzyValue(value);
}
