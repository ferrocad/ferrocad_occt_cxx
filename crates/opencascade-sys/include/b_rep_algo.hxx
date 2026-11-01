#include <BRepAlgo_Image.hxx>
#include <BRepAlgo_NormalProjection.hxx>
#include <GeomAbs_Shape.hxx>
#include <Standard_Failure.hxx>
#include <TopTools_ListOfShape.hxx>
#include <TopoDS_Shape.hxx>
#include <bindings_common.hxx>
#include <stdexcept>

inline void b_rep_algo_rethrow(const Standard_Failure &e) {
  const char *msg = e.GetMessageString();
  throw std::runtime_error(msg ? msg : "OpenCASCADE Standard_Failure");
}

inline std::unique_ptr<BRepAlgo_NormalProjection>
BRepAlgo_NormalProjection_new(const TopoDS_Shape &target) {
  try {
    return std::unique_ptr<BRepAlgo_NormalProjection>(new BRepAlgo_NormalProjection(target));
  } catch (const Standard_Failure &e) {
    b_rep_algo_rethrow(e);
    return nullptr;
  }
}

inline void BRepAlgo_NormalProjection_Compute3d(BRepAlgo_NormalProjection &projection,
                                                bool with_3d) {
  try {
    projection.Compute3d(with_3d);
  } catch (const Standard_Failure &e) {
    b_rep_algo_rethrow(e);
  }
}

inline void BRepAlgo_NormalProjection_Build(BRepAlgo_NormalProjection &projection) {
  try {
    projection.Build();
  } catch (const Standard_Failure &e) {
    b_rep_algo_rethrow(e);
  }
}
