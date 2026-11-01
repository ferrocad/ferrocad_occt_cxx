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

// OCCT 8 turned `class TopoDS` into `namespace TopoDS`, so the casts can no
// longer be bound as static members. These free wrappers spell `TopoDS::X(..)`,
// which is valid against both the 7.8 class and the 8.x namespace.
inline const TopoDS_Vertex &topods_vertex(const TopoDS_Shape &shape) {
  return TopoDS::Vertex(shape);
}
inline const TopoDS_Edge &topods_edge(const TopoDS_Shape &shape) {
  return TopoDS::Edge(shape);
}
inline const TopoDS_Wire &topods_wire(const TopoDS_Shape &shape) {
  return TopoDS::Wire(shape);
}
inline const TopoDS_Face &topods_face(const TopoDS_Shape &shape) {
  return TopoDS::Face(shape);
}
inline const TopoDS_Shell &topods_shell(const TopoDS_Shape &shape) {
  return TopoDS::Shell(shape);
}
inline const TopoDS_Solid &topods_solid(const TopoDS_Shape &shape) {
  return TopoDS::Solid(shape);
}
inline const TopoDS_Compound &topods_compound(const TopoDS_Shape &shape) {
  return TopoDS::Compound(shape);
}

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
