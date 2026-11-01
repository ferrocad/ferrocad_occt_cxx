#include <BRepAlgoAPI_BuilderAlgo.hxx>
#include <BRepAlgoAPI_Common.hxx>
#include <BRepAlgoAPI_Cut.hxx>
#include <BRepAlgoAPI_Fuse.hxx>
#include <BRepAlgoAPI_Section.hxx>
#include <bindings_common.hxx>

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
