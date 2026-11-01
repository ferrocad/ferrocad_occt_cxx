#include <BRepFill.hxx>
#include <BRepFill_Filling.hxx>
#include <GeomAbs_Shape.hxx>
#include <Standard_Failure.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Face.hxx>
#include <bindings_common.hxx>
#include <stdexcept>

inline void b_rep_fill_rethrow(const Standard_Failure &e) {
  const char *msg = e.GetMessageString();
  throw std::runtime_error(msg ? msg : "OpenCASCADE Standard_Failure");
}

inline std::unique_ptr<TopoDS_Face> BRepFill_Face(const TopoDS_Edge &edge1,
                                                  const TopoDS_Edge &edge2) {
  try {
    return std::unique_ptr<TopoDS_Face>(new TopoDS_Face(BRepFill::Face(edge1, edge2)));
  } catch (const Standard_Failure &e) {
    b_rep_fill_rethrow(e);
    return nullptr;
  }
}

inline void BRepFill_Filling_Build(BRepFill_Filling &filling) {
  try {
    filling.Build();
  } catch (const Standard_Failure &e) {
    b_rep_fill_rethrow(e);
  }
}

inline std::unique_ptr<TopoDS_Face> BRepFill_Filling_Face(const BRepFill_Filling &filling) {
  return std::unique_ptr<TopoDS_Face>(new TopoDS_Face(filling.Face()));
}
