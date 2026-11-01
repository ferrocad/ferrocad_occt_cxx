#include <BRepProj_Projection.hxx>
#include <Standard_Failure.hxx>
#include <TopoDS_Compound.hxx>
#include <TopoDS_Shape.hxx>
#include <gp_Dir.hxx>
#include <gp_Pnt.hxx>
#include <bindings_common.hxx>
#include <stdexcept>

inline void b_rep_proj_rethrow(const Standard_Failure &e) {
  const char *msg = e.GetMessageString();
  throw std::runtime_error(msg ? msg : "OpenCASCADE Standard_Failure");
}

inline std::unique_ptr<BRepProj_Projection>
BRepProj_Projection_dir_new(const TopoDS_Shape &tool, const TopoDS_Shape &target, const gp_Dir &dir) {
  try {
    return std::unique_ptr<BRepProj_Projection>(new BRepProj_Projection(tool, target, dir));
  } catch (const Standard_Failure &e) {
    b_rep_proj_rethrow(e);
    return nullptr;
  }
}

inline std::unique_ptr<BRepProj_Projection>
BRepProj_Projection_pnt_new(const TopoDS_Shape &tool, const TopoDS_Shape &target, const gp_Pnt &pnt) {
  try {
    return std::unique_ptr<BRepProj_Projection>(new BRepProj_Projection(tool, target, pnt));
  } catch (const Standard_Failure &e) {
    b_rep_proj_rethrow(e);
    return nullptr;
  }
}

inline std::unique_ptr<TopoDS_Compound>
BRepProj_Projection_Shape(const BRepProj_Projection &projection) {
  return std::unique_ptr<TopoDS_Compound>(new TopoDS_Compound(projection.Shape()));
}
