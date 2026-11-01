#pragma once

// Typed bindings for OCCT's ChFi2d package.
//
// The algorithms are plain C++ classes owned by `unique_ptr`; each method is
// `const` because it mutates through the pointer. OCCT exceptions are
// translated to `std::exception` here, so cxx's `Result` shim delivers `Err`.
// There are no FerroCAD status codes (`-1`, null sentinels) in this crate.

#include <ChFi2d_AnaFilletAlgo.hxx>
#include <ChFi2d_ChamferAPI.hxx>
#include <ChFi2d_FilletAlgo.hxx>
#include <Standard_Failure.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS_Wire.hxx>
#include <gp_Dir.hxx>
#include <gp_Pln.hxx>
#include <gp_Pnt.hxx>

#include <memory>
#include <stdexcept>

namespace chfi2d_internal
{
inline gp_Pln plane(double ox, double oy, double oz, double nx, double ny, double nz)
{
    return gp_Pln(gp_Pnt(ox, oy, oz), gp_Dir(nx, ny, nz));
}

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

// The three edges an algorithm returns: the new fillet/chamfer edge followed by
// the two trimmed input edges.
class ChFi2dEdgeTriple
{
public:
    TopoDS_Shape first;
    TopoDS_Shape second;
    TopoDS_Shape third;

    const TopoDS_Shape& first_shape() const { return first; }
    const TopoDS_Shape& second_shape() const { return second; }
    const TopoDS_Shape& third_shape() const { return third; }

    bool first_is_null() const { return first.IsNull(); }
    bool second_is_null() const { return second.IsNull(); }
    bool third_is_null() const { return third.IsNull(); }
};

// --- ChFi2d_FilletAlgo -----------------------------------------------------

class ChFi2dFilletAlgo
{
public:
    std::unique_ptr<ChFi2d_FilletAlgo> algo;

    ChFi2dFilletAlgo() : algo(std::make_unique<ChFi2d_FilletAlgo>()) {}

    void init_wire(const TopoDS_Shape& wire, double ox, double oy, double oz, double nx,
                   double ny, double nz) const
    {
        chfi2d_internal::guarded([&] {
            algo->Init(TopoDS::Wire(wire), chfi2d_internal::plane(ox, oy, oz, nx, ny, nz));
        });
    }

    void init_edges(const TopoDS_Shape& edge1, const TopoDS_Shape& edge2, double ox,
                    double oy, double oz, double nx, double ny, double nz) const
    {
        chfi2d_internal::guarded([&] {
            algo->Init(TopoDS::Edge(edge1), TopoDS::Edge(edge2),
                       chfi2d_internal::plane(ox, oy, oz, nx, ny, nz));
        });
    }

    bool perform(double radius) const
    {
        return chfi2d_internal::guarded([&] { return algo->Perform(radius); });
    }

    int nb_results(double x, double y, double z) const
    {
        return chfi2d_internal::guarded([&] { return algo->NbResults(gp_Pnt(x, y, z)); });
    }

    std::unique_ptr<ChFi2dEdgeTriple> result(double x, double y, double z,
                                             int solution) const
    {
        return chfi2d_internal::guarded([&] {
            TopoDS_Edge edge1;
            TopoDS_Edge edge2;
            TopoDS_Edge fillet = algo->Result(gp_Pnt(x, y, z), edge1, edge2, solution);
            auto out = std::make_unique<ChFi2dEdgeTriple>();
            out->first = fillet;
            out->second = edge1;
            out->third = edge2;
            return out;
        });
    }
};

inline std::unique_ptr<ChFi2dFilletAlgo> chfi2d_fillet_algo_new()
{
    return std::make_unique<ChFi2dFilletAlgo>();
}

// --- ChFi2d_AnaFilletAlgo --------------------------------------------------

class ChFi2dAnaFilletAlgo
{
public:
    std::unique_ptr<ChFi2d_AnaFilletAlgo> algo;

    ChFi2dAnaFilletAlgo() : algo(std::make_unique<ChFi2d_AnaFilletAlgo>()) {}

    void init_wire(const TopoDS_Shape& wire, double ox, double oy, double oz, double nx,
                   double ny, double nz) const
    {
        chfi2d_internal::guarded([&] {
            algo->Init(TopoDS::Wire(wire), chfi2d_internal::plane(ox, oy, oz, nx, ny, nz));
        });
    }

    void init_edges(const TopoDS_Shape& edge1, const TopoDS_Shape& edge2, double ox,
                    double oy, double oz, double nx, double ny, double nz) const
    {
        chfi2d_internal::guarded([&] {
            algo->Init(TopoDS::Edge(edge1), TopoDS::Edge(edge2),
                       chfi2d_internal::plane(ox, oy, oz, nx, ny, nz));
        });
    }

    bool perform(double radius) const
    {
        return chfi2d_internal::guarded([&] { return algo->Perform(radius); });
    }

    std::unique_ptr<ChFi2dEdgeTriple> result() const
    {
        return chfi2d_internal::guarded([&] {
            TopoDS_Edge edge1;
            TopoDS_Edge edge2;
            TopoDS_Shape fillet = algo->Result(edge1, edge2);
            auto out = std::make_unique<ChFi2dEdgeTriple>();
            out->first = fillet;
            out->second = edge1;
            out->third = edge2;
            return out;
        });
    }
};

inline std::unique_ptr<ChFi2dAnaFilletAlgo> chfi2d_ana_fillet_algo_new()
{
    return std::make_unique<ChFi2dAnaFilletAlgo>();
}

// --- ChFi2d_ChamferAPI -----------------------------------------------------

class ChFi2dChamferApi
{
public:
    std::unique_ptr<ChFi2d_ChamferAPI> algo;

    ChFi2dChamferApi() : algo(std::make_unique<ChFi2d_ChamferAPI>()) {}

    void init_wire(const TopoDS_Shape& wire) const
    {
        chfi2d_internal::guarded([&] { algo->Init(TopoDS::Wire(wire)); });
    }

    void init_edges(const TopoDS_Shape& edge1, const TopoDS_Shape& edge2) const
    {
        chfi2d_internal::guarded([&] {
            algo->Init(TopoDS::Edge(edge1), TopoDS::Edge(edge2));
        });
    }

    bool perform() const
    {
        return chfi2d_internal::guarded([&] { return algo->Perform(); });
    }

    std::unique_ptr<ChFi2dEdgeTriple> result(double length1, double length2) const
    {
        return chfi2d_internal::guarded([&] {
            TopoDS_Edge edge1;
            TopoDS_Edge edge2;
            TopoDS_Edge chamfer = algo->Result(edge1, edge2, length1, length2);
            auto out = std::make_unique<ChFi2dEdgeTriple>();
            out->first = chamfer;
            out->second = edge1;
            out->third = edge2;
            return out;
        });
    }
};

inline std::unique_ptr<ChFi2dChamferApi> chfi2d_chamfer_api_new()
{
    return std::make_unique<ChFi2dChamferApi>();
}
