#include <BRepAlgo_Image.hxx>
#include <BRepBuilderAPI_TransitionMode.hxx>
#include <BRepOffset_MakeOffset.hxx>
#include <BRepOffsetAPI_MakeOffset.hxx>
#include <BRepOffsetAPI_MakeOffsetShape.hxx>
#include <BRepOffsetAPI_MakePipe.hxx>
#include <BRepOffsetAPI_MakePipeShell.hxx>
#include <BRepOffsetAPI_MakeThickSolid.hxx>
#include <BRepOffsetAPI_ThruSections.hxx>
#include <Law_Function.hxx>
#include <Standard_Failure.hxx>
#include <TopTools_ListOfShape.hxx>
#include <TopoDS_Shape.hxx>
#include <bindings_common.hxx>
#include <stdexcept>

// MSVC only: a
// member-function pointer to `BRepOffsetAPI_MakePipeShell::SetLaw`
// doesn't exact-match `Handle_Law_Function` (a distinct subclass of
// `opencascade::handle<Law_Function>` under MSVC) against OCCT's own
// `Handle(Law_Function)`-typed parameter. A free-function wrapper
// sidesteps the pointer-type binding.
inline void BRepOffsetAPI_MakePipeShell_SetLaw(BRepOffsetAPI_MakePipeShell &shell, const TopoDS_Shape &profile,
                                               const Handle_Law_Function &law, bool with_contact,
                                               bool with_correction) {
  shell.SetLaw(profile, law, with_contact, with_correction);
}

inline void BRepOffsetAPI_MakeOffsetShape_PerformByJoin(BRepOffsetAPI_MakeOffsetShape &self,
                                                        const TopoDS_Shape &source, double offset,
                                                        double tolerance, BRepOffset_Mode mode,
                                                        bool intersection, bool self_intersection,
                                                        GeomAbs_JoinType join) {
  try {
    self.PerformByJoin(source, offset, tolerance, mode, intersection, self_intersection, join);
  } catch (const Standard_Failure &e) {
    const char *msg = e.GetMessageString();
    throw std::runtime_error(msg ? msg : "OpenCASCADE Standard_Failure");
  }
}

inline const BRepAlgo_Image &
BRepOffsetAPI_MakeOffsetShape_OffsetEdgesFromShapes(const BRepOffsetAPI_MakeOffsetShape &self) {
  return self.MakeOffset().OffsetEdgesFromShapes();
}
