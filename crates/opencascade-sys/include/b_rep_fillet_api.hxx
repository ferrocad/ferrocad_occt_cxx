#include <BRepFilletAPI_MakeChamfer.hxx>
#include <BRepFilletAPI_MakeFillet.hxx>
#include <BRepFilletAPI_MakeFillet2d.hxx>
#include <Message_ProgressRange.hxx>
#include <Standard_Failure.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Shape.hxx>
#include <TopTools_ListOfShape.hxx>
#include <bindings_common.hxx>

#include <stdexcept>

inline std::unique_ptr<TopoDS_Edge> BRepFilletAPI_MakeFillet2d_add_fillet(BRepFilletAPI_MakeFillet2d &make_fillet,
                                                                          const TopoDS_Vertex &vertex,
                                                                          Standard_Real radius) {
  return std::unique_ptr<TopoDS_Edge>(new TopoDS_Edge(make_fillet.AddFillet(vertex, radius)));
}

// Chamfers
inline std::unique_ptr<TopoDS_Edge>
BRepFilletAPI_MakeFillet2d_add_chamfer(BRepFilletAPI_MakeFillet2d &make_fillet, const TopoDS_Edge &edge1,
                                       const TopoDS_Edge &edge2, const Standard_Real dist1, const Standard_Real dist2) {
  return std::unique_ptr<TopoDS_Edge>(new TopoDS_Edge(make_fillet.AddChamfer(edge1, edge2, dist1, dist2)));
}

inline std::unique_ptr<TopoDS_Edge>
BRepFilletAPI_MakeFillet2d_add_chamfer_angle(BRepFilletAPI_MakeFillet2d &make_fillet, const TopoDS_Edge &edge,
                                             const TopoDS_Vertex &vertex, const Standard_Real dist,
                                             const Standard_Real angle) {
  return std::unique_ptr<TopoDS_Edge>(new TopoDS_Edge(make_fillet.AddChamfer(edge, vertex, dist, angle)));
}

// --- fallible build --------------------------------------------------------
// `BRepFilletAPI_MakeFillet::Build` and `BRepFilletAPI_MakeChamfer::Build` can
// raise `Standard_Failure`, which on OCCT 7.x does not derive from
// `std::exception`. Translate it into `std::runtime_error` so cxx's `Result`
// shim delivers the failure as `Err` instead of aborting via `std::terminate`.
namespace b_rep_fillet_internal
{
[[noreturn]] inline void rethrow(const Standard_Failure& f)
{
    const char* m = f.GetMessageString();
    throw std::runtime_error(m && *m ? m : "OCCT reported a failure");
}

template <typename Op>
inline void build(Op& op)
{
    try
    {
        op.Build(Message_ProgressRange());
    }
    catch (const Standard_Failure& f)
    {
        rethrow(f);
    }
    catch (const std::exception&)
    {
        throw;
    }
    catch (...)
    {
        throw std::runtime_error("unknown OCCT exception");
    }
}
}  // namespace b_rep_fillet_internal

inline void BRepFilletAPI_MakeFillet_build(BRepFilletAPI_MakeFillet& op)
{
    b_rep_fillet_internal::build(op);
}

inline void BRepFilletAPI_MakeChamfer_build(BRepFilletAPI_MakeChamfer& op)
{
    b_rep_fillet_internal::build(op);
}
