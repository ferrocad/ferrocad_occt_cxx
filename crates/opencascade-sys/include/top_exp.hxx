#include <TopExp.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS_Vertex.hxx>
#include <TopoDS_Wire.hxx>
#include <bindings_common.hxx>

inline std::unique_ptr<TopoDS_Shape> ExplorerCurrentShape(const TopExp_Explorer &explorer) {
  return std::unique_ptr<TopoDS_Shape>(new TopoDS_Shape(explorer.Current()));
}

inline std::unique_ptr<TopoDS_Vertex> TopExp_FirstVertex(const TopoDS_Edge &edge) {
  return std::unique_ptr<TopoDS_Vertex>(new TopoDS_Vertex(TopExp::FirstVertex(edge)));
}

inline std::unique_ptr<TopoDS_Vertex> TopExp_LastVertex(const TopoDS_Edge &edge) {
  return std::unique_ptr<TopoDS_Vertex>(new TopoDS_Vertex(TopExp::LastVertex(edge)));
}

inline std::unique_ptr<TopoDS_Vertex> TopExp_FirstVertex_Oriented(const TopoDS_Edge &edge,
                                                                 const Standard_Boolean cum_ori) {
  return std::unique_ptr<TopoDS_Vertex>(new TopoDS_Vertex(TopExp::FirstVertex(edge, cum_ori)));
}

inline std::unique_ptr<TopoDS_Vertex> TopExp_LastVertex_Oriented(const TopoDS_Edge &edge,
                                                                const Standard_Boolean cum_ori) {
  return std::unique_ptr<TopoDS_Vertex>(new TopoDS_Vertex(TopExp::LastVertex(edge, cum_ori)));
}

// `TopExp_Explorer(S, ToFind, ToAvoid)`: explore `ToFind` sub-shapes without
// descending into `ToAvoid` ones (`TopAbs_SHAPE` avoids nothing).
inline std::unique_ptr<TopExp_Explorer> TopExp_Explorer_new_avoid(const TopoDS_Shape &shape,
                                                                  TopAbs_ShapeEnum to_find,
                                                                  TopAbs_ShapeEnum to_avoid) {
  return std::unique_ptr<TopExp_Explorer>(new TopExp_Explorer(shape, to_find, to_avoid));
}
