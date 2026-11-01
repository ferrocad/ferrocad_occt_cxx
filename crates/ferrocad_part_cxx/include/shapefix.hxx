#pragma once

// FerroCAD: the `ShapeFix_*` wrappers behind `Part.ShapeFix`.
//
// `opencascade-sys` 0.3 does not bridge OCCT's shape-fixing tools, so this is a
// sibling cxx bridge (like `fc_history.hxx`) over the same global `TopoDS_*`
// types. Every wrapper method is `const`: the OCCT fixer lives behind a
// `Handle`, whose `operator->` is const, so no `Pin` is needed on the Rust side
// and a fixer can be called through a shared reference.
//
// Every fallible method throws a `std::exception` on OCCT failure; the cxx
// bridge declares those methods as `Result`, and the Rust layer maps the error
// to `Part.OCCError`. No exception may cross the bridge.

#include <BRep_Tool.hxx>
#include <Geom_Plane.hxx>
#include <ShapeFix_Edge.hxx>
#include <ShapeFix_Face.hxx>
#include <ShapeFix_Root.hxx>
#include <ShapeFix_Shape.hxx>
#include <ShapeFix_Shell.hxx>
#include <ShapeFix_Solid.hxx>
#include <ShapeFix_Wire.hxx>
#include <Standard_Failure.hxx>
#include <TopAbs_ShapeEnum.hxx>
#include <TopExp_Explorer.hxx>
#include <TopLoc_Location.hxx>
#include <TopTools_SequenceOfShape.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS_Shell.hxx>
#include <TopoDS_Solid.hxx>
#include <TopoDS_Vertex.hxx>
#include <TopoDS_Wire.hxx>
#include <gp_Dir.hxx>
#include <gp_Pln.hxx>
#include <gp_Pnt.hxx>

#include <memory>
#include <stdexcept>
#include <vector>

#include "rust/cxx.h"

// Translate an OCCT failure for cxx's `Result` shim. OCCT 7.x's
// `Standard_Failure` is not a `std::exception`; note that a bad `TopoDS` cast
// raises `Standard_TypeMismatch`, which also derives from `Standard_Failure`.
namespace fc_shapefix_internal
{
[[noreturn]] inline void rethrow(const Standard_Failure& failure)
{
    const char* message = failure.GetMessageString();
    throw std::runtime_error(message && *message ? message : "OCCT reported a failure");
}
}  // namespace fc_shapefix_internal

#define FC_SHAPEFIX_CATCH                                                   \
    catch (const Standard_Failure& failure)                               \
    {                                                                      \
        fc_shapefix_internal::rethrow(failure);                            \
    }                                                                      \
    catch (const std::exception&)                                          \
    {                                                                      \
        throw;                                                             \
    }                                                                      \
    catch (...)                                                            \
    {                                                                      \
        throw std::runtime_error("unknown OCCT exception");                \
    }

// Root methods shared by every fixer derived from `ShapeFix_Root`. `h` is the
// concrete handle member every wrapper class declares.
#define FC_SHAPEFIX_ROOT_METHODS                                               \
    void set_precision(double value) const { h->SetPrecision(value); }         \
    double precision() const { return h->Precision(); }                        \
    void set_min_tolerance(double value) const { h->SetMinTolerance(value); }  \
    double min_tolerance() const { return h->MinTolerance(); }                 \
    void set_max_tolerance(double value) const { h->SetMaxTolerance(value); }  \
    double max_tolerance() const { return h->MaxTolerance(); }                 \
    double limit_tolerance(double value) const { return h->LimitTolerance(value); }

namespace fc_shapefix_internal
{
// A plane through `origin` with direction `normal`.
inline gp_Pln plane(double ox, double oy, double oz, double nx, double ny, double nz)
{
    return gp_Pln(gp_Pnt(ox, oy, oz), gp_Dir(nx, ny, nz));
}

// A plane whose normal is given but whose origin is a point of `anchor`. Used
// for the surface overloads of `ShapeFix_Edge`, where Python hands us a
// `Face.Surface` (a normal, no location) and an edge that lies on it: any
// vertex of the edge is a point of the surface.
inline Handle(Geom_Plane) anchor_plane(const TopoDS_Shape& anchor, double nx, double ny, double nz)
{
    gp_Pnt origin(0.0, 0.0, 0.0);
    for (TopExp_Explorer it(anchor, TopAbs_VERTEX); it.More(); it.Next()) {
        origin = BRep_Tool::Pnt(TopoDS::Vertex(it.Current()));
        break;
    }
    return new Geom_Plane(gp_Pln(origin, gp_Dir(nx, ny, nz)));
}

inline Handle(Geom_Plane) plane_handle(double ox, double oy, double oz,
                                       double nx, double ny, double nz)
{
    return new Geom_Plane(plane(ox, oy, oz, nx, ny, nz));
}
}  // namespace fc_shapefix_internal

// --- Root ------------------------------------------------------------------

class FcShapeFixRoot
{
public:
    Handle(ShapeFix_Root) h;
    FcShapeFixRoot() : h(new ShapeFix_Root()) {}
    FC_SHAPEFIX_ROOT_METHODS
};

inline std::unique_ptr<FcShapeFixRoot> fc_shapefix_root_new()
{
    return std::make_unique<FcShapeFixRoot>();
}

// --- Edge ------------------------------------------------------------------

class FcShapeFixEdge
{
public:
    Handle(ShapeFix_Edge) h;
    FcShapeFixEdge() : h(new ShapeFix_Edge()) {}
    explicit FcShapeFixEdge(const Handle(ShapeFix_Edge)& handle) : h(handle) {}

    bool fix_remove_pcurve_face(const TopoDS_Shape& edge, const TopoDS_Shape& face) const
    {
        try {
            return h->FixRemovePCurve(TopoDS::Edge(edge), TopoDS::Face(face));
        }
        FC_SHAPEFIX_CATCH
    }

    bool fix_remove_pcurve_surface(const TopoDS_Shape& edge, double nx, double ny,
                                   double nz) const
    {
        try {
            return h->FixRemovePCurve(TopoDS::Edge(edge),
                                      fc_shapefix_internal::anchor_plane(edge, nx, ny, nz),
                                      TopLoc_Location());
        }
        FC_SHAPEFIX_CATCH
    }

    bool fix_remove_curve3d(const TopoDS_Shape& edge) const
    {
        try {
            return h->FixRemoveCurve3d(TopoDS::Edge(edge));
        }
        FC_SHAPEFIX_CATCH
    }

    bool fix_add_pcurve_face(const TopoDS_Shape& edge, const TopoDS_Shape& face,
                             bool seam, double prec) const
    {
        try {
            return h->FixAddPCurve(TopoDS::Edge(edge), TopoDS::Face(face), seam, prec);
        }
        FC_SHAPEFIX_CATCH
    }

    bool fix_add_pcurve_surface(const TopoDS_Shape& edge, double nx, double ny,
                                double nz, bool seam, double prec) const
    {
        try {
            return h->FixAddPCurve(TopoDS::Edge(edge),
                                   fc_shapefix_internal::anchor_plane(edge, nx, ny, nz),
                                   TopLoc_Location(), seam, prec);
        }
        FC_SHAPEFIX_CATCH
    }

    bool fix_add_curve3d(const TopoDS_Shape& edge) const
    {
        try {
            return h->FixAddCurve3d(TopoDS::Edge(edge));
        }
        FC_SHAPEFIX_CATCH
    }

    bool fix_vertex_tolerance_face(const TopoDS_Shape& edge, const TopoDS_Shape& face) const
    {
        try {
            return h->FixVertexTolerance(TopoDS::Edge(edge), TopoDS::Face(face));
        }
        FC_SHAPEFIX_CATCH
    }

    bool fix_vertex_tolerance(const TopoDS_Shape& edge) const
    {
        try {
            return h->FixVertexTolerance(TopoDS::Edge(edge));
        }
        FC_SHAPEFIX_CATCH
    }

    bool fix_reversed2d_face(const TopoDS_Shape& edge, const TopoDS_Shape& face) const
    {
        try {
            return h->FixReversed2d(TopoDS::Edge(edge), TopoDS::Face(face));
        }
        FC_SHAPEFIX_CATCH
    }

    bool fix_reversed2d_surface(const TopoDS_Shape& edge, double nx, double ny,
                                double nz) const
    {
        try {
            return h->FixReversed2d(TopoDS::Edge(edge),
                                    fc_shapefix_internal::anchor_plane(edge, nx, ny, nz),
                                    TopLoc_Location());
        }
        FC_SHAPEFIX_CATCH
    }

    bool fix_same_parameter(const TopoDS_Shape& edge, double tolerance) const
    {
        try {
            return h->FixSameParameter(TopoDS::Edge(edge), tolerance);
        }
        FC_SHAPEFIX_CATCH
    }

    bool fix_same_parameter_face(const TopoDS_Shape& edge, const TopoDS_Shape& face,
                                 double tolerance) const
    {
        try {
            return h->FixSameParameter(TopoDS::Edge(edge), TopoDS::Face(face), tolerance);
        }
        FC_SHAPEFIX_CATCH
    }
};

inline std::unique_ptr<FcShapeFixEdge> fc_shapefix_edge_new()
{
    return std::make_unique<FcShapeFixEdge>();
}

// --- Wire ------------------------------------------------------------------

class FcShapeFixWire
{
public:
    Handle(ShapeFix_Wire) h;
    FcShapeFixWire() : h(new ShapeFix_Wire()) {}
    explicit FcShapeFixWire(const Handle(ShapeFix_Wire)& handle) : h(handle) {}

    FC_SHAPEFIX_ROOT_METHODS

    void init(const TopoDS_Shape& wire, const TopoDS_Shape& face, double prec) const
    {
        try {
            h->Init(TopoDS::Wire(wire), TopoDS::Face(face), prec);
        }
        FC_SHAPEFIX_CATCH
    }

    bool load(const TopoDS_Shape& wire) const
    {
        try {
            h->Load(TopoDS::Wire(wire));
            return true;
        }
        FC_SHAPEFIX_CATCH
    }

    bool set_face(const TopoDS_Shape& face) const
    {
        try {
            h->SetFace(TopoDS::Face(face));
            return true;
        }
        FC_SHAPEFIX_CATCH
    }

    bool set_surface(double ox, double oy, double oz, double nx, double ny, double nz) const
    {
        try {
            h->SetSurface(fc_shapefix_internal::plane_handle(ox, oy, oz, nx, ny, nz));
            return true;
        }
        FC_SHAPEFIX_CATCH
    }

    bool set_surface_placed(double ox, double oy, double oz, double nx, double ny,
                            double nz) const
    {
        try {
            // A `Part.Plane` is already expressed in world coordinates, so the
            // optional placement is the identity (see the module docs).
            h->SetSurface(fc_shapefix_internal::plane_handle(ox, oy, oz, nx, ny, nz),
                          TopLoc_Location());
            return true;
        }
        FC_SHAPEFIX_CATCH
    }

    void set_max_tail_angle(double angle) const { h->SetMaxTailAngle(angle); }
    void set_max_tail_width(double width) const { h->SetMaxTailWidth(width); }
    bool is_loaded() const { return h->IsLoaded(); }
    bool is_ready() const { return h->IsReady(); }
    int nb_edges() const { return h->NbEdges(); }

    std::unique_ptr<TopoDS_Shape> wire() const
    {
        try {
            return std::make_unique<TopoDS_Shape>(h->Wire());
        }
        FC_SHAPEFIX_CATCH
    }

    std::unique_ptr<TopoDS_Shape> wire_api_make() const
    {
        try {
            return std::make_unique<TopoDS_Shape>(h->WireAPIMake());
        }
        FC_SHAPEFIX_CATCH
    }

    std::unique_ptr<TopoDS_Shape> face() const
    {
        try {
            return std::make_unique<TopoDS_Shape>(h->Face());
        }
        FC_SHAPEFIX_CATCH
    }

    bool perform() const
    {
        try {
            return h->Perform();
        }
        FC_SHAPEFIX_CATCH
    }

    void clear_modes() const { h->ClearModes(); }
    void clear_statuses() const { h->ClearStatuses(); }

    std::unique_ptr<FcShapeFixEdge> fix_edge_tool() const
    {
        return std::make_unique<FcShapeFixEdge>(h->FixEdgeTool());
    }

    bool fix_reorder() const
    {
        try {
            return h->FixReorder();
        }
        FC_SHAPEFIX_CATCH
    }

    int fix_small_global(bool lock, double prec) const
    {
        try {
            return h->FixSmall(lock, prec);
        }
        FC_SHAPEFIX_CATCH
    }

    bool fix_small_one(int num, bool lock, double prec) const
    {
        try {
            return h->FixSmall(num, lock, prec);
        }
        FC_SHAPEFIX_CATCH
    }

    bool fix_connected(double prec) const
    {
        try {
            return h->FixConnected(prec);
        }
        FC_SHAPEFIX_CATCH
    }

    bool fix_connected_one(int num, double prec) const
    {
        try {
            return h->FixConnected(num, prec);
        }
        FC_SHAPEFIX_CATCH
    }

    bool fix_edge_curves() const
    {
        try {
            return h->FixEdgeCurves();
        }
        FC_SHAPEFIX_CATCH
    }

    bool fix_degenerated() const
    {
        try {
            return h->FixDegenerated();
        }
        FC_SHAPEFIX_CATCH
    }

    bool fix_degenerated_one(int num) const
    {
        try {
            return h->FixDegenerated(num);
        }
        FC_SHAPEFIX_CATCH
    }

    bool fix_self_intersection() const
    {
        try {
            return h->FixSelfIntersection();
        }
        FC_SHAPEFIX_CATCH
    }

    bool fix_lacking(bool force) const
    {
        try {
            return h->FixLacking(force);
        }
        FC_SHAPEFIX_CATCH
    }

    bool fix_lacking_one(int num, bool force) const
    {
        try {
            return h->FixLacking(num, force);
        }
        FC_SHAPEFIX_CATCH
    }

    bool fix_closed(double prec) const
    {
        try {
            return h->FixClosed(prec);
        }
        FC_SHAPEFIX_CATCH
    }

    bool fix_gaps3d() const
    {
        try {
            return h->FixGaps3d();
        }
        FC_SHAPEFIX_CATCH
    }

    bool fix_gaps2d() const
    {
        try {
            return h->FixGaps2d();
        }
        FC_SHAPEFIX_CATCH
    }

    bool fix_seam(int num) const
    {
        try {
            return h->FixSeam(num);
        }
        FC_SHAPEFIX_CATCH
    }

    bool fix_shifted() const
    {
        try {
            return h->FixShifted();
        }
        FC_SHAPEFIX_CATCH
    }

    bool fix_notched_edges() const
    {
        try {
            return h->FixNotchedEdges();
        }
        FC_SHAPEFIX_CATCH
    }

    bool fix_gap3d(int num, bool convert) const
    {
        try {
            return h->FixGap3d(num, convert);
        }
        FC_SHAPEFIX_CATCH
    }

    bool fix_gap2d(int num, bool convert) const
    {
        try {
            return h->FixGap2d(num, convert);
        }
        FC_SHAPEFIX_CATCH
    }

    bool fix_tails() const
    {
        try {
            return h->FixTails();
        }
        FC_SHAPEFIX_CATCH
    }

    // `ModifyTopologyMode` / `ModifyGeometryMode` / `ClosedWireMode` /
    // `PreferencePCurveMode` / `FixGapsByRangesMode` are `Standard_Boolean&`.
    bool modify_topology_mode() const { return h->ModifyTopologyMode(); }
    void set_modify_topology_mode(bool value) const { h->ModifyTopologyMode() = value; }
    bool modify_geometry_mode() const { return h->ModifyGeometryMode(); }
    void set_modify_geometry_mode(bool value) const { h->ModifyGeometryMode() = value; }
    bool closed_wire_mode() const { return h->ClosedWireMode(); }
    void set_closed_wire_mode(bool value) const { h->ClosedWireMode() = value; }
    bool preference_pcurve_mode() const { return h->PreferencePCurveMode(); }
    void set_preference_pcurve_mode(bool value) const { h->PreferencePCurveMode() = value; }
    bool fix_gaps_by_ranges_mode() const { return h->FixGapsByRangesMode(); }
    void set_fix_gaps_by_ranges_mode(bool value) const { h->FixGapsByRangesMode() = value; }

    // The remaining modes are `Standard_Integer&`, with -1 meaning "default".
    int modify_remove_loop_mode() const { return h->ModifyRemoveLoopMode(); }
    void set_modify_remove_loop_mode(int value) const { h->ModifyRemoveLoopMode() = value; }
    int fix_reorder_mode() const { return h->FixReorderMode(); }
    void set_fix_reorder_mode(int value) const { h->FixReorderMode() = value; }
    int fix_small_mode() const { return h->FixSmallMode(); }
    void set_fix_small_mode(int value) const { h->FixSmallMode() = value; }
    int fix_connected_mode() const { return h->FixConnectedMode(); }
    void set_fix_connected_mode(int value) const { h->FixConnectedMode() = value; }
    int fix_edge_curves_mode() const { return h->FixEdgeCurvesMode(); }
    void set_fix_edge_curves_mode(int value) const { h->FixEdgeCurvesMode() = value; }
    int fix_degenerated_mode() const { return h->FixDegeneratedMode(); }
    void set_fix_degenerated_mode(int value) const { h->FixDegeneratedMode() = value; }
    int fix_self_intersection_mode() const { return h->FixSelfIntersectionMode(); }
    void set_fix_self_intersection_mode(int value) const
    {
        h->FixSelfIntersectionMode() = value;
    }
    int fix_lacking_mode() const { return h->FixLackingMode(); }
    void set_fix_lacking_mode(int value) const { h->FixLackingMode() = value; }
    int fix_gaps3d_mode() const { return h->FixGaps3dMode(); }
    void set_fix_gaps3d_mode(int value) const { h->FixGaps3dMode() = value; }
    int fix_gaps2d_mode() const { return h->FixGaps2dMode(); }
    void set_fix_gaps2d_mode(int value) const { h->FixGaps2dMode() = value; }
    int fix_reversed2d_mode() const { return h->FixReversed2dMode(); }
    void set_fix_reversed2d_mode(int value) const { h->FixReversed2dMode() = value; }
    int fix_remove_pcurve_mode() const { return h->FixRemovePCurveMode(); }
    void set_fix_remove_pcurve_mode(int value) const { h->FixRemovePCurveMode() = value; }
    int fix_add_pcurve_mode() const { return h->FixAddPCurveMode(); }
    void set_fix_add_pcurve_mode(int value) const { h->FixAddPCurveMode() = value; }
    int fix_remove_curve3d_mode() const { return h->FixRemoveCurve3dMode(); }
    void set_fix_remove_curve3d_mode(int value) const
    {
        h->FixRemoveCurve3dMode() = value;
    }
    int fix_add_curve3d_mode() const { return h->FixAddCurve3dMode(); }
    void set_fix_add_curve3d_mode(int value) const { h->FixAddCurve3dMode() = value; }
    int fix_seam_mode() const { return h->FixSeamMode(); }
    void set_fix_seam_mode(int value) const { h->FixSeamMode() = value; }
    int fix_shifted_mode() const { return h->FixShiftedMode(); }
    void set_fix_shifted_mode(int value) const { h->FixShiftedMode() = value; }
    int fix_same_parameter_mode() const { return h->FixSameParameterMode(); }
    void set_fix_same_parameter_mode(int value) const { h->FixSameParameterMode() = value; }
    int fix_vertex_tolerance_mode() const { return h->FixVertexToleranceMode(); }
    void set_fix_vertex_tolerance_mode(int value) const
    {
        h->FixVertexToleranceMode() = value;
    }
    int fix_notched_edges_mode() const { return h->FixNotchedEdgesMode(); }
    void set_fix_notched_edges_mode(int value) const { h->FixNotchedEdgesMode() = value; }
    int fix_self_intersecting_edge_mode() const { return h->FixSelfIntersectingEdgeMode(); }
    void set_fix_self_intersecting_edge_mode(int value) const
    {
        h->FixSelfIntersectingEdgeMode() = value;
    }
    int fix_intersecting_edges_mode() const { return h->FixIntersectingEdgesMode(); }
    void set_fix_intersecting_edges_mode(int value) const
    {
        h->FixIntersectingEdgesMode() = value;
    }
    int fix_non_adjacent_intersecting_edges_mode() const
    {
        return h->FixNonAdjacentIntersectingEdgesMode();
    }
    void set_fix_non_adjacent_intersecting_edges_mode(int value) const
    {
        h->FixNonAdjacentIntersectingEdgesMode() = value;
    }
    int fix_tail_mode() const { return h->FixTailMode(); }
    void set_fix_tail_mode(int value) const { h->FixTailMode() = value; }
};

inline std::unique_ptr<FcShapeFixWire> fc_shapefix_wire_new()
{
    return std::make_unique<FcShapeFixWire>();
}

inline std::unique_ptr<FcShapeFixWire> fc_shapefix_wire_from_wire(const TopoDS_Shape& wire,
                                                                  const TopoDS_Shape& face,
                                                                  double prec)
{
    try {
        return std::make_unique<FcShapeFixWire>(new ShapeFix_Wire(
            TopoDS::Wire(wire), TopoDS::Face(face), prec));
    }
    FC_SHAPEFIX_CATCH
}

// --- A list of shapes (the output of `ShapeFix_Face::FixLoopWire`) ----------

class FcShapeList
{
public:
    bool ok = false;
    std::vector<TopoDS_Shape> items;

    bool is_ok() const { return ok; }
    std::size_t size() const { return items.size(); }
    const TopoDS_Shape& at(std::size_t index) const { return items.at(index); }
};

// --- Face ------------------------------------------------------------------

class FcShapeFixFace
{
public:
    Handle(ShapeFix_Face) h;
    FcShapeFixFace() : h(new ShapeFix_Face()) {}
    explicit FcShapeFixFace(const Handle(ShapeFix_Face)& handle) : h(handle) {}

    FC_SHAPEFIX_ROOT_METHODS

    bool init_face(const TopoDS_Shape& face) const
    {
        try {
            h->Init(TopoDS::Face(face));
            return true;
        }
        FC_SHAPEFIX_CATCH
    }

    bool init_plane(double ox, double oy, double oz, double nx, double ny, double nz,
                    double prec, bool fwd) const
    {
        try {
            h->Init(fc_shapefix_internal::plane_handle(ox, oy, oz, nx, ny, nz), prec, fwd);
            return true;
        }
        FC_SHAPEFIX_CATCH
    }

    bool add(const TopoDS_Shape& wire) const
    {
        try {
            h->Add(TopoDS::Wire(wire));
            return true;
        }
        FC_SHAPEFIX_CATCH
    }

    bool perform() const
    {
        try {
            return h->Perform();
        }
        FC_SHAPEFIX_CATCH
    }

    bool fix_orientation() const
    {
        try {
            return h->FixOrientation();
        }
        FC_SHAPEFIX_CATCH
    }

    bool fix_add_natural_bound() const
    {
        try {
            return h->FixAddNaturalBound();
        }
        FC_SHAPEFIX_CATCH
    }

    bool fix_missing_seam() const
    {
        try {
            return h->FixMissingSeam();
        }
        FC_SHAPEFIX_CATCH
    }

    bool fix_small_area_wire(bool remove_small) const
    {
        try {
            return h->FixSmallAreaWire(remove_small);
        }
        FC_SHAPEFIX_CATCH
    }

    std::unique_ptr<FcShapeList> fix_loop_wire() const
    {
        auto out = std::make_unique<FcShapeList>();
        try {
            TopTools_SequenceOfShape wires;
            out->ok = h->FixLoopWire(wires);
            for (Standard_Integer i = 1; i <= wires.Length(); ++i) {
                out->items.push_back(wires.Value(i));
            }
        }
        FC_SHAPEFIX_CATCH
        return out;
    }

    bool fix_intersecting_wires() const
    {
        try {
            return h->FixIntersectingWires();
        }
        FC_SHAPEFIX_CATCH
    }

    bool fix_wires_two_coincident_edges() const
    {
        try {
            return h->FixWiresTwoCoincEdges();
        }
        FC_SHAPEFIX_CATCH
    }

    bool fix_periodic_degenerated() const
    {
        try {
            return h->FixPeriodicDegenerated();
        }
        FC_SHAPEFIX_CATCH
    }

    std::unique_ptr<TopoDS_Shape> face() const
    {
        try {
            return std::make_unique<TopoDS_Shape>(h->Face());
        }
        FC_SHAPEFIX_CATCH
    }

    std::unique_ptr<TopoDS_Shape> result() const
    {
        try {
            return std::make_unique<TopoDS_Shape>(h->Result());
        }
        FC_SHAPEFIX_CATCH
    }

    std::unique_ptr<FcShapeFixWire> fix_wire_tool() const
    {
        return std::make_unique<FcShapeFixWire>(h->FixWireTool());
    }

    void clear_modes() const { h->ClearModes(); }

    int fix_wire_mode() const { return h->FixWireMode(); }
    void set_fix_wire_mode(int value) const { h->FixWireMode() = value; }
    int fix_orientation_mode() const { return h->FixOrientationMode(); }
    void set_fix_orientation_mode(int value) const { h->FixOrientationMode() = value; }
    int fix_add_natural_bound_mode() const { return h->FixAddNaturalBoundMode(); }
    void set_fix_add_natural_bound_mode(int value) const
    {
        h->FixAddNaturalBoundMode() = value;
    }
    int fix_missing_seam_mode() const { return h->FixMissingSeamMode(); }
    void set_fix_missing_seam_mode(int value) const { h->FixMissingSeamMode() = value; }
    int fix_small_area_wire_mode() const { return h->FixSmallAreaWireMode(); }
    void set_fix_small_area_wire_mode(int value) const { h->FixSmallAreaWireMode() = value; }
    int remove_small_area_face_mode() const { return h->RemoveSmallAreaFaceMode(); }
    void set_remove_small_area_face_mode(int value) const
    {
        h->RemoveSmallAreaFaceMode() = value;
    }
    int fix_intersecting_wires_mode() const { return h->FixIntersectingWiresMode(); }
    void set_fix_intersecting_wires_mode(int value) const
    {
        h->FixIntersectingWiresMode() = value;
    }
    int fix_loop_wires_mode() const { return h->FixLoopWiresMode(); }
    void set_fix_loop_wires_mode(int value) const { h->FixLoopWiresMode() = value; }
    int fix_split_face_mode() const { return h->FixSplitFaceMode(); }
    void set_fix_split_face_mode(int value) const { h->FixSplitFaceMode() = value; }
    int auto_correct_precision_mode() const { return h->AutoCorrectPrecisionMode(); }
    void set_auto_correct_precision_mode(int value) const
    {
        h->AutoCorrectPrecisionMode() = value;
    }
    int fix_periodic_degenerated_mode() const { return h->FixPeriodicDegeneratedMode(); }
    void set_fix_periodic_degenerated_mode(int value) const
    {
        h->FixPeriodicDegeneratedMode() = value;
    }
};

inline std::unique_ptr<FcShapeFixFace> fc_shapefix_face_new()
{
    return std::make_unique<FcShapeFixFace>();
}

inline std::unique_ptr<FcShapeFixFace> fc_shapefix_face_from_face(const TopoDS_Shape& face)
{
    try {
        return std::make_unique<FcShapeFixFace>(new ShapeFix_Face(TopoDS::Face(face)));
    }
    FC_SHAPEFIX_CATCH
}

inline std::unique_ptr<FcShapeFixFace> fc_shapefix_face_from_plane(double ox, double oy,
                                                                   double oz, double nx,
                                                                   double ny, double nz,
                                                                   double prec, bool fwd)
{
    try {
        Handle(ShapeFix_Face) fix = new ShapeFix_Face();
        fix->Init(fc_shapefix_internal::plane_handle(ox, oy, oz, nx, ny, nz), prec, fwd);
        return std::make_unique<FcShapeFixFace>(fix);
    }
    FC_SHAPEFIX_CATCH
}

// --- Shell -----------------------------------------------------------------

class FcShapeFixShell
{
public:
    Handle(ShapeFix_Shell) h;
    FcShapeFixShell() : h(new ShapeFix_Shell()) {}
    explicit FcShapeFixShell(const Handle(ShapeFix_Shell)& handle) : h(handle) {}

    FC_SHAPEFIX_ROOT_METHODS

    bool init(const TopoDS_Shape& shell) const
    {
        try {
            h->Init(TopoDS::Shell(shell));
            return true;
        }
        FC_SHAPEFIX_CATCH
    }

    bool perform() const
    {
        try {
            return h->Perform();
        }
        FC_SHAPEFIX_CATCH
    }

    std::unique_ptr<TopoDS_Shape> shell() const
    {
        try {
            return std::make_unique<TopoDS_Shape>(h->Shell());
        }
        FC_SHAPEFIX_CATCH
    }

    std::unique_ptr<TopoDS_Shape> shape() const
    {
        try {
            return std::make_unique<TopoDS_Shape>(h->Shape());
        }
        FC_SHAPEFIX_CATCH
    }

    std::unique_ptr<TopoDS_Shape> error_faces() const
    {
        try {
            return std::make_unique<TopoDS_Shape>(h->ErrorFaces());
        }
        FC_SHAPEFIX_CATCH
    }

    int nb_shells() const { return h->NbShells(); }

    std::unique_ptr<FcShapeFixFace> fix_face_tool() const
    {
        return std::make_unique<FcShapeFixFace>(h->FixFaceTool());
    }

    bool fix_face_orientation(const TopoDS_Shape& shell, bool multi_connex,
                              bool non_manifold) const
    {
        try {
            return h->FixFaceOrientation(TopoDS::Shell(shell), multi_connex, non_manifold);
        }
        FC_SHAPEFIX_CATCH
    }

    void set_non_manifold_flag(bool value) const { h->SetNonManifoldFlag(value); }

    int fix_face_mode() const { return h->FixFaceMode(); }
    void set_fix_face_mode(int value) const { h->FixFaceMode() = value; }
    int fix_orientation_mode() const { return h->FixOrientationMode(); }
    void set_fix_orientation_mode(int value) const { h->FixOrientationMode() = value; }
};

inline std::unique_ptr<FcShapeFixShell> fc_shapefix_shell_new()
{
    return std::make_unique<FcShapeFixShell>();
}

inline std::unique_ptr<FcShapeFixShell> fc_shapefix_shell_from_shell(const TopoDS_Shape& shell)
{
    try {
        return std::make_unique<FcShapeFixShell>(new ShapeFix_Shell(TopoDS::Shell(shell)));
    }
    FC_SHAPEFIX_CATCH
}

// --- Solid -----------------------------------------------------------------

class FcShapeFixSolid
{
public:
    Handle(ShapeFix_Solid) h;
    FcShapeFixSolid() : h(new ShapeFix_Solid()) {}
    explicit FcShapeFixSolid(const Handle(ShapeFix_Solid)& handle) : h(handle) {}

    FC_SHAPEFIX_ROOT_METHODS

    bool init(const TopoDS_Shape& solid) const
    {
        try {
            h->Init(TopoDS::Solid(solid));
            return true;
        }
        FC_SHAPEFIX_CATCH
    }

    bool perform() const
    {
        try {
            return h->Perform();
        }
        FC_SHAPEFIX_CATCH
    }

    std::unique_ptr<TopoDS_Shape> solid_from_shell(const TopoDS_Shape& shell) const
    {
        try {
            return std::make_unique<TopoDS_Shape>(h->SolidFromShell(TopoDS::Shell(shell)));
        }
        FC_SHAPEFIX_CATCH
    }

    std::unique_ptr<TopoDS_Shape> solid() const
    {
        try {
            return std::make_unique<TopoDS_Shape>(h->Solid());
        }
        FC_SHAPEFIX_CATCH
    }

    std::unique_ptr<TopoDS_Shape> shape() const
    {
        try {
            return std::make_unique<TopoDS_Shape>(h->Shape());
        }
        FC_SHAPEFIX_CATCH
    }

    std::unique_ptr<FcShapeFixShell> fix_shell_tool() const
    {
        return std::make_unique<FcShapeFixShell>(h->FixShellTool());
    }

    int fix_shell_mode() const { return h->FixShellMode(); }
    void set_fix_shell_mode(int value) const { h->FixShellMode() = value; }
    int fix_shell_orientation_mode() const { return h->FixShellOrientationMode(); }
    void set_fix_shell_orientation_mode(int value) const
    {
        h->FixShellOrientationMode() = value;
    }
    bool create_open_solid_mode() const { return h->CreateOpenSolidMode(); }
    void set_create_open_solid_mode(bool value) const
    {
        h->CreateOpenSolidMode() = value;
    }
};

inline std::unique_ptr<FcShapeFixSolid> fc_shapefix_solid_new()
{
    return std::make_unique<FcShapeFixSolid>();
}

inline std::unique_ptr<FcShapeFixSolid> fc_shapefix_solid_from_solid(const TopoDS_Shape& solid)
{
    try {
        return std::make_unique<FcShapeFixSolid>(new ShapeFix_Solid(TopoDS::Solid(solid)));
    }
    FC_SHAPEFIX_CATCH
}

// --- Shape -----------------------------------------------------------------

class FcShapeFixShape
{
public:
    Handle(ShapeFix_Shape) h;
    FcShapeFixShape() : h(new ShapeFix_Shape()) {}
    explicit FcShapeFixShape(const Handle(ShapeFix_Shape)& handle) : h(handle) {}

    FC_SHAPEFIX_ROOT_METHODS

    bool init(const TopoDS_Shape& shape) const
    {
        try {
            h->Init(shape);
            return true;
        }
        FC_SHAPEFIX_CATCH
    }

    bool perform() const
    {
        try {
            return h->Perform();
        }
        FC_SHAPEFIX_CATCH
    }

    std::unique_ptr<TopoDS_Shape> shape() const
    {
        try {
            return std::make_unique<TopoDS_Shape>(h->Shape());
        }
        FC_SHAPEFIX_CATCH
    }

    std::unique_ptr<FcShapeFixSolid> fix_solid_tool() const
    {
        return std::make_unique<FcShapeFixSolid>(h->FixSolidTool());
    }

    std::unique_ptr<FcShapeFixShell> fix_shell_tool() const
    {
        return std::make_unique<FcShapeFixShell>(h->FixShellTool());
    }

    std::unique_ptr<FcShapeFixFace> fix_face_tool() const
    {
        return std::make_unique<FcShapeFixFace>(h->FixFaceTool());
    }

    std::unique_ptr<FcShapeFixWire> fix_wire_tool() const
    {
        return std::make_unique<FcShapeFixWire>(h->FixWireTool());
    }

    std::unique_ptr<FcShapeFixEdge> fix_edge_tool() const
    {
        return std::make_unique<FcShapeFixEdge>(h->FixEdgeTool());
    }

    int fix_solid_mode() const { return h->FixSolidMode(); }
    void set_fix_solid_mode(int value) const { h->FixSolidMode() = value; }
    int fix_free_shell_mode() const { return h->FixFreeShellMode(); }
    void set_fix_free_shell_mode(int value) const { h->FixFreeShellMode() = value; }
    int fix_free_face_mode() const { return h->FixFreeFaceMode(); }
    void set_fix_free_face_mode(int value) const { h->FixFreeFaceMode() = value; }
    int fix_free_wire_mode() const { return h->FixFreeWireMode(); }
    void set_fix_free_wire_mode(int value) const { h->FixFreeWireMode() = value; }
    int fix_same_parameter_mode() const { return h->FixSameParameterMode(); }
    void set_fix_same_parameter_mode(int value) const { h->FixSameParameterMode() = value; }
    int fix_vertex_position_mode() const { return h->FixVertexPositionMode(); }
    void set_fix_vertex_position_mode(int value) const
    {
        h->FixVertexPositionMode() = value;
    }
    int fix_vertex_tol_mode() const { return h->FixVertexTolMode(); }
    void set_fix_vertex_tol_mode(int value) const { h->FixVertexTolMode() = value; }
};

inline std::unique_ptr<FcShapeFixShape> fc_shapefix_shape_new()
{
    return std::make_unique<FcShapeFixShape>();
}

inline std::unique_ptr<FcShapeFixShape> fc_shapefix_shape_from_shape(const TopoDS_Shape& shape)
{
    try {
        return std::make_unique<FcShapeFixShape>(new ShapeFix_Shape(shape));
    }
    FC_SHAPEFIX_CATCH
}
