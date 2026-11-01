#pragma once

// Typed bindings for OCCT's ChFi2d package.
//
// The algorithms are plain C++ classes. The empty constructors are bound via
// `construct_unique` (see bindings_common.hxx); every `Init`/`Perform`/
// `NbResults`/`Result` call can throw `Standard_Failure`, which on OCCT 7.x does
// not derive from `std::exception`. Those calls therefore go through a small
// `guarded` shim that catches `Standard_Failure` and rethrows it as a
// `std::runtime_error`, which cxx's `Result` shim delivers as `Err`.

#include <ChFi2d_AnaFilletAlgo.hxx>
#include <ChFi2d_ChamferAPI.hxx>
#include <ChFi2d_FilletAlgo.hxx>
#include <Standard_Failure.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Wire.hxx>
#include <gp_Pln.hxx>
#include <gp_Pnt.hxx>
#include <bindings_common.hxx>

#include <stdexcept>

namespace chfi2d_internal
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
}  // namespace chfi2d_internal

// --- ChFi2d_FilletAlgo -----------------------------------------------------

inline void ChFi2d_FilletAlgo_Init(ChFi2d_FilletAlgo& algo, const TopoDS_Wire& wire,
                                   const gp_Pln& plane)
{
    chfi2d_internal::guarded([&] { algo.Init(wire, plane); });
}

inline void ChFi2d_FilletAlgo_Init_edges(ChFi2d_FilletAlgo& algo, const TopoDS_Edge& edge1,
                                         const TopoDS_Edge& edge2, const gp_Pln& plane)
{
    chfi2d_internal::guarded([&] { algo.Init(edge1, edge2, plane); });
}

inline bool ChFi2d_FilletAlgo_Perform(ChFi2d_FilletAlgo& algo, double radius)
{
    return chfi2d_internal::guarded([&] { return algo.Perform(radius); });
}

inline int ChFi2d_FilletAlgo_NbResults(ChFi2d_FilletAlgo& algo, const gp_Pnt& point)
{
    return chfi2d_internal::guarded([&] { return algo.NbResults(point); });
}

inline std::unique_ptr<TopoDS_Edge> ChFi2d_FilletAlgo_Result(ChFi2d_FilletAlgo& algo,
                                                             const gp_Pnt& point, int solution,
                                                             TopoDS_Edge& edge1, TopoDS_Edge& edge2)
{
    return chfi2d_internal::guarded([&] {
        TopoDS_Edge fillet = algo.Result(point, edge1, edge2, solution);
        return std::unique_ptr<TopoDS_Edge>(new TopoDS_Edge(fillet));
    });
}

// --- ChFi2d_AnaFilletAlgo --------------------------------------------------

inline void ChFi2d_AnaFilletAlgo_Init(ChFi2d_AnaFilletAlgo& algo, const TopoDS_Wire& wire,
                                      const gp_Pln& plane)
{
    chfi2d_internal::guarded([&] { algo.Init(wire, plane); });
}

inline void ChFi2d_AnaFilletAlgo_Init_edges(ChFi2d_AnaFilletAlgo& algo, const TopoDS_Edge& edge1,
                                            const TopoDS_Edge& edge2, const gp_Pln& plane)
{
    chfi2d_internal::guarded([&] { algo.Init(edge1, edge2, plane); });
}

inline bool ChFi2d_AnaFilletAlgo_Perform(ChFi2d_AnaFilletAlgo& algo, double radius)
{
    return chfi2d_internal::guarded([&] { return algo.Perform(radius); });
}

inline std::unique_ptr<TopoDS_Edge> ChFi2d_AnaFilletAlgo_Result(ChFi2d_AnaFilletAlgo& algo,
                                                                TopoDS_Edge& edge1,
                                                                TopoDS_Edge& edge2)
{
    return chfi2d_internal::guarded([&] {
        // `Result` returns a `const TopoDS_Edge&` into the algorithm's own
        // member, so copy it before the algorithm object can be destroyed.
        const TopoDS_Edge& fillet = algo.Result(edge1, edge2);
        return std::unique_ptr<TopoDS_Edge>(new TopoDS_Edge(fillet));
    });
}

// --- ChFi2d_ChamferAPI -----------------------------------------------------

inline void ChFi2d_ChamferAPI_Init(ChFi2d_ChamferAPI& algo, const TopoDS_Wire& wire)
{
    chfi2d_internal::guarded([&] { algo.Init(wire); });
}

inline void ChFi2d_ChamferAPI_Init_edges(ChFi2d_ChamferAPI& algo, const TopoDS_Edge& edge1,
                                         const TopoDS_Edge& edge2)
{
    chfi2d_internal::guarded([&] { algo.Init(edge1, edge2); });
}

inline bool ChFi2d_ChamferAPI_Perform(ChFi2d_ChamferAPI& algo)
{
    return chfi2d_internal::guarded([&] { return algo.Perform(); });
}

inline std::unique_ptr<TopoDS_Edge> ChFi2d_ChamferAPI_Result(ChFi2d_ChamferAPI& algo,
                                                             double length1, double length2,
                                                             TopoDS_Edge& edge1, TopoDS_Edge& edge2)
{
    return chfi2d_internal::guarded([&] {
        TopoDS_Edge chamfer = algo.Result(edge1, edge2, length1, length2);
        return std::unique_ptr<TopoDS_Edge>(new TopoDS_Edge(chamfer));
    });
}
