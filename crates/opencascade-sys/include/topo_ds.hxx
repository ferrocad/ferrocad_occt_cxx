#include <TopTools_ListOfShape.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Builder.hxx>
#include <TopoDS_Compound.hxx>
#include <TopoDS_CompSolid.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Iterator.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS_Shell.hxx>
#include <TopoDS_Solid.hxx>
#include <TopoDS_TShape.hxx>
#include <TopoDS_Vertex.hxx>
#include <bindings_common.hxx>

#include <cstdint>

// `Complement()` mutates in place and `Complemented()` returns by value, which
// cxx cannot express for an opaque type.
inline std::unique_ptr<TopoDS_Shape> shape_complement(const TopoDS_Shape &shape) {
  return std::unique_ptr<TopoDS_Shape>(new TopoDS_Shape(shape.Complemented()));
}

inline std::unique_ptr<TopoDS_Shape> Reversed(const TopoDS_Shape &shape) {
  return std::unique_ptr<TopoDS_Shape>(new TopoDS_Shape(shape.Reversed()));
}

inline uintptr_t TopoDS_Shape_t_shape_ptr(const TopoDS_Shape &shape) {
  return reinterpret_cast<uintptr_t>(shape.TShape().get());
}
