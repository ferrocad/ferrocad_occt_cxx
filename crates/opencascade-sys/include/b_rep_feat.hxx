#include <BRepFeat_MakeCylindricalHole.hxx>
#include <BRepFeat_MakeDPrism.hxx>
#include <BRepFeat_SplitShape.hxx>
#include <Standard_Failure.hxx>
#include <TopoDS_Compound.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS_Wire.hxx>
#include <bindings_common.hxx>

#include <stdexcept>

namespace b_rep_feat_internal
{
[[noreturn]] inline void rethrow(const Standard_Failure& failure)
{
    const char* message = failure.GetMessageString();
    throw std::runtime_error(message && *message ? message : "OCCT reported a failure");
}

// Run one OCCT call and translate its failure type for cxx's `Result` shim.
template <typename F>
inline auto guarded(F&& call) -> decltype(call())
{
    try
    {
        return call();
    }
    catch (const Standard_Failure& failure)
    {
        rethrow(failure);
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
}  // namespace b_rep_feat_internal

// --- BRepFeat_SplitShape ---------------------------------------------------

inline void BRepFeat_SplitShape_Add_wire_face(BRepFeat_SplitShape& split, const TopoDS_Wire& wire,
                                              const TopoDS_Face& face)
{
    b_rep_feat_internal::guarded([&] { split.Add(wire, face); });
}

inline void BRepFeat_SplitShape_Add_edge_face(BRepFeat_SplitShape& split, const TopoDS_Edge& edge,
                                              const TopoDS_Face& face)
{
    b_rep_feat_internal::guarded([&] { split.Add(edge, face); });
}

inline void BRepFeat_SplitShape_Add_compound_face(BRepFeat_SplitShape& split,
                                                  const TopoDS_Compound& compound,
                                                  const TopoDS_Face& face)
{
    b_rep_feat_internal::guarded([&] { split.Add(compound, face); });
}

inline void BRepFeat_SplitShape_Add_edge_edge(BRepFeat_SplitShape& split, const TopoDS_Edge& edge,
                                              const TopoDS_Edge& edge_on)
{
    b_rep_feat_internal::guarded([&] { split.Add(edge, edge_on); });
}

inline void BRepFeat_SplitShape_Build(BRepFeat_SplitShape& split)
{
    b_rep_feat_internal::guarded([&] { split.Build(); });
}
