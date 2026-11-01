#include <BOPAlgo_BuilderFace.hxx>
#include <BOPAlgo_GlueEnum.hxx>
#include <BOPAlgo_Operation.hxx>
#include <Standard_Failure.hxx>
#include <TopoDS_Face.hxx>
#include <TopTools_ListOfShape.hxx>
#include <bindings_common.hxx>

#include <stdexcept>

inline void BOPAlgo_BuilderFace_Perform(BOPAlgo_BuilderFace &builder_face) {
  try {
    builder_face.Perform();
  } catch (const Standard_Failure &e) {
    const char *msg = e.GetMessageString();
    throw std::runtime_error(msg && *msg ? msg : "BOPAlgo_BuilderFace::Perform failed");
  }
}
