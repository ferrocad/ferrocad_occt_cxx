//! Typed bindings for OCCT's ShapeFix package.

#[cxx::bridge]
mod ffi {
    unsafe extern "C++" {
            include!("ferrocad_part_cxx/include/shapefix.hxx");

            type TopoDS_Shape = opencascade_sys::topo_ds::TopoDS_Shape;

            type FcShapeFixRoot;
            type FcShapeFixEdge;
            type FcShapeFixWire;
            type FcShapeFixFace;
            type FcShapeFixShell;
            type FcShapeFixSolid;
            type FcShapeFixShape;
            type FcShapeList;

            // --- Root ------------------------------------------------------
            fn fc_shapefix_root_new() -> UniquePtr<FcShapeFixRoot>;
            fn set_precision(self: &FcShapeFixRoot, value: f64);
            fn precision(self: &FcShapeFixRoot) -> f64;
            fn set_min_tolerance(self: &FcShapeFixRoot, value: f64);
            fn min_tolerance(self: &FcShapeFixRoot) -> f64;
            fn set_max_tolerance(self: &FcShapeFixRoot, value: f64);
            fn max_tolerance(self: &FcShapeFixRoot) -> f64;
            fn limit_tolerance(self: &FcShapeFixRoot, value: f64) -> f64;

            // --- Edge ------------------------------------------------------
            fn fc_shapefix_edge_new() -> UniquePtr<FcShapeFixEdge>;
            fn fix_remove_pcurve_face(
                self: &FcShapeFixEdge,
                edge: &TopoDS_Shape,
                face: &TopoDS_Shape,
            ) -> Result<bool>;
            fn fix_remove_pcurve_surface(
                self: &FcShapeFixEdge,
                edge: &TopoDS_Shape,
                nx: f64,
                ny: f64,
                nz: f64,
            ) -> Result<bool>;
            fn fix_remove_curve3d(self: &FcShapeFixEdge, edge: &TopoDS_Shape) -> Result<bool>;
            fn fix_add_pcurve_face(
                self: &FcShapeFixEdge,
                edge: &TopoDS_Shape,
                face: &TopoDS_Shape,
                seam: bool,
                prec: f64,
            ) -> Result<bool>;
            fn fix_add_pcurve_surface(
                self: &FcShapeFixEdge,
                edge: &TopoDS_Shape,
                nx: f64,
                ny: f64,
                nz: f64,
                seam: bool,
                prec: f64,
            ) -> Result<bool>;
            fn fix_add_curve3d(self: &FcShapeFixEdge, edge: &TopoDS_Shape) -> Result<bool>;
            fn fix_vertex_tolerance_face(
                self: &FcShapeFixEdge,
                edge: &TopoDS_Shape,
                face: &TopoDS_Shape,
            ) -> Result<bool>;
            fn fix_vertex_tolerance(self: &FcShapeFixEdge, edge: &TopoDS_Shape) -> Result<bool>;
            fn fix_reversed2d_face(
                self: &FcShapeFixEdge,
                edge: &TopoDS_Shape,
                face: &TopoDS_Shape,
            ) -> Result<bool>;
            fn fix_reversed2d_surface(
                self: &FcShapeFixEdge,
                edge: &TopoDS_Shape,
                nx: f64,
                ny: f64,
                nz: f64,
            ) -> Result<bool>;
            fn fix_same_parameter(
                self: &FcShapeFixEdge,
                edge: &TopoDS_Shape,
                tolerance: f64,
            ) -> Result<bool>;
            fn fix_same_parameter_face(
                self: &FcShapeFixEdge,
                edge: &TopoDS_Shape,
                face: &TopoDS_Shape,
                tolerance: f64,
            ) -> Result<bool>;

            // --- Wire ------------------------------------------------------
            fn fc_shapefix_wire_new() -> UniquePtr<FcShapeFixWire>;
            fn fc_shapefix_wire_from_wire(
                wire: &TopoDS_Shape,
                face: &TopoDS_Shape,
                prec: f64,
            ) -> Result<UniquePtr<FcShapeFixWire>>;
            fn init(
                self: &FcShapeFixWire,
                wire: &TopoDS_Shape,
                face: &TopoDS_Shape,
                prec: f64,
            ) -> Result<()>;
            fn load(self: &FcShapeFixWire, wire: &TopoDS_Shape) -> Result<bool>;
            fn set_precision(self: &FcShapeFixWire, value: f64);
            fn set_face(self: &FcShapeFixWire, face: &TopoDS_Shape) -> Result<bool>;
            fn set_surface(
                self: &FcShapeFixWire,
                ox: f64,
                oy: f64,
                oz: f64,
                nx: f64,
                ny: f64,
                nz: f64,
            ) -> Result<bool>;
            fn set_surface_placed(
                self: &FcShapeFixWire,
                ox: f64,
                oy: f64,
                oz: f64,
                nx: f64,
                ny: f64,
                nz: f64,
            ) -> Result<bool>;
            fn set_max_tail_angle(self: &FcShapeFixWire, angle: f64);
            fn set_max_tail_width(self: &FcShapeFixWire, width: f64);
            fn is_loaded(self: &FcShapeFixWire) -> bool;
            fn is_ready(self: &FcShapeFixWire) -> bool;
            fn nb_edges(self: &FcShapeFixWire) -> i32;
            fn wire(self: &FcShapeFixWire) -> Result<UniquePtr<TopoDS_Shape>>;
            fn wire_api_make(self: &FcShapeFixWire) -> Result<UniquePtr<TopoDS_Shape>>;
            fn face(self: &FcShapeFixWire) -> Result<UniquePtr<TopoDS_Shape>>;
            fn perform(self: &FcShapeFixWire) -> Result<bool>;
            fn clear_modes(self: &FcShapeFixWire);
            fn clear_statuses(self: &FcShapeFixWire);
            fn fix_edge_tool(self: &FcShapeFixWire) -> UniquePtr<FcShapeFixEdge>;
            fn fix_reorder(self: &FcShapeFixWire) -> Result<bool>;
            fn fix_small_global(self: &FcShapeFixWire, lock: bool, prec: f64) -> Result<i32>;
            fn fix_small_one(
                self: &FcShapeFixWire,
                num: i32,
                lock: bool,
                prec: f64,
            ) -> Result<bool>;
            fn fix_connected(self: &FcShapeFixWire, prec: f64) -> Result<bool>;
            fn fix_connected_one(self: &FcShapeFixWire, num: i32, prec: f64) -> Result<bool>;
            fn fix_edge_curves(self: &FcShapeFixWire) -> Result<bool>;
            fn fix_degenerated(self: &FcShapeFixWire) -> Result<bool>;
            fn fix_degenerated_one(self: &FcShapeFixWire, num: i32) -> Result<bool>;
            fn fix_self_intersection(self: &FcShapeFixWire) -> Result<bool>;
            fn fix_lacking(self: &FcShapeFixWire, force: bool) -> Result<bool>;
            fn fix_lacking_one(self: &FcShapeFixWire, num: i32, force: bool) -> Result<bool>;
            fn fix_closed(self: &FcShapeFixWire, prec: f64) -> Result<bool>;
            fn fix_gaps3d(self: &FcShapeFixWire) -> Result<bool>;
            fn fix_gaps2d(self: &FcShapeFixWire) -> Result<bool>;
            fn fix_seam(self: &FcShapeFixWire, num: i32) -> Result<bool>;
            fn fix_shifted(self: &FcShapeFixWire) -> Result<bool>;
            fn fix_notched_edges(self: &FcShapeFixWire) -> Result<bool>;
            fn fix_gap3d(self: &FcShapeFixWire, num: i32, convert: bool) -> Result<bool>;
            fn fix_gap2d(self: &FcShapeFixWire, num: i32, convert: bool) -> Result<bool>;
            fn fix_tails(self: &FcShapeFixWire) -> Result<bool>;
            fn modify_topology_mode(self: &FcShapeFixWire) -> bool;
            fn set_modify_topology_mode(self: &FcShapeFixWire, value: bool);
            fn modify_geometry_mode(self: &FcShapeFixWire) -> bool;
            fn set_modify_geometry_mode(self: &FcShapeFixWire, value: bool);
            fn closed_wire_mode(self: &FcShapeFixWire) -> bool;
            fn set_closed_wire_mode(self: &FcShapeFixWire, value: bool);
            fn preference_pcurve_mode(self: &FcShapeFixWire) -> bool;
            fn set_preference_pcurve_mode(self: &FcShapeFixWire, value: bool);
            fn fix_gaps_by_ranges_mode(self: &FcShapeFixWire) -> bool;
            fn set_fix_gaps_by_ranges_mode(self: &FcShapeFixWire, value: bool);
            fn modify_remove_loop_mode(self: &FcShapeFixWire) -> i32;
            fn set_modify_remove_loop_mode(self: &FcShapeFixWire, value: i32);
            fn fix_reorder_mode(self: &FcShapeFixWire) -> i32;
            fn set_fix_reorder_mode(self: &FcShapeFixWire, value: i32);
            fn fix_small_mode(self: &FcShapeFixWire) -> i32;
            fn set_fix_small_mode(self: &FcShapeFixWire, value: i32);
            fn fix_connected_mode(self: &FcShapeFixWire) -> i32;
            fn set_fix_connected_mode(self: &FcShapeFixWire, value: i32);
            fn fix_edge_curves_mode(self: &FcShapeFixWire) -> i32;
            fn set_fix_edge_curves_mode(self: &FcShapeFixWire, value: i32);
            fn fix_degenerated_mode(self: &FcShapeFixWire) -> i32;
            fn set_fix_degenerated_mode(self: &FcShapeFixWire, value: i32);
            fn fix_self_intersection_mode(self: &FcShapeFixWire) -> i32;
            fn set_fix_self_intersection_mode(self: &FcShapeFixWire, value: i32);
            fn fix_lacking_mode(self: &FcShapeFixWire) -> i32;
            fn set_fix_lacking_mode(self: &FcShapeFixWire, value: i32);
            fn fix_gaps3d_mode(self: &FcShapeFixWire) -> i32;
            fn set_fix_gaps3d_mode(self: &FcShapeFixWire, value: i32);
            fn fix_gaps2d_mode(self: &FcShapeFixWire) -> i32;
            fn set_fix_gaps2d_mode(self: &FcShapeFixWire, value: i32);
            fn fix_reversed2d_mode(self: &FcShapeFixWire) -> i32;
            fn set_fix_reversed2d_mode(self: &FcShapeFixWire, value: i32);
            fn fix_remove_pcurve_mode(self: &FcShapeFixWire) -> i32;
            fn set_fix_remove_pcurve_mode(self: &FcShapeFixWire, value: i32);
            fn fix_add_pcurve_mode(self: &FcShapeFixWire) -> i32;
            fn set_fix_add_pcurve_mode(self: &FcShapeFixWire, value: i32);
            fn fix_remove_curve3d_mode(self: &FcShapeFixWire) -> i32;
            fn set_fix_remove_curve3d_mode(self: &FcShapeFixWire, value: i32);
            fn fix_add_curve3d_mode(self: &FcShapeFixWire) -> i32;
            fn set_fix_add_curve3d_mode(self: &FcShapeFixWire, value: i32);
            fn fix_seam_mode(self: &FcShapeFixWire) -> i32;
            fn set_fix_seam_mode(self: &FcShapeFixWire, value: i32);
            fn fix_shifted_mode(self: &FcShapeFixWire) -> i32;
            fn set_fix_shifted_mode(self: &FcShapeFixWire, value: i32);
            fn fix_same_parameter_mode(self: &FcShapeFixWire) -> i32;
            fn set_fix_same_parameter_mode(self: &FcShapeFixWire, value: i32);
            fn fix_vertex_tolerance_mode(self: &FcShapeFixWire) -> i32;
            fn set_fix_vertex_tolerance_mode(self: &FcShapeFixWire, value: i32);
            fn fix_notched_edges_mode(self: &FcShapeFixWire) -> i32;
            fn set_fix_notched_edges_mode(self: &FcShapeFixWire, value: i32);
            fn fix_self_intersecting_edge_mode(self: &FcShapeFixWire) -> i32;
            fn set_fix_self_intersecting_edge_mode(self: &FcShapeFixWire, value: i32);
            fn fix_intersecting_edges_mode(self: &FcShapeFixWire) -> i32;
            fn set_fix_intersecting_edges_mode(self: &FcShapeFixWire, value: i32);
            fn fix_non_adjacent_intersecting_edges_mode(self: &FcShapeFixWire) -> i32;
            fn set_fix_non_adjacent_intersecting_edges_mode(
                self: &FcShapeFixWire,
                value: i32,
            );
            fn fix_tail_mode(self: &FcShapeFixWire) -> i32;
            fn set_fix_tail_mode(self: &FcShapeFixWire, value: i32);

            // --- Face ------------------------------------------------------
            fn fc_shapefix_face_new() -> UniquePtr<FcShapeFixFace>;
            fn fc_shapefix_face_from_face(face: &TopoDS_Shape) -> Result<UniquePtr<FcShapeFixFace>>;
            fn fc_shapefix_face_from_plane(
                ox: f64,
                oy: f64,
                oz: f64,
                nx: f64,
                ny: f64,
                nz: f64,
                prec: f64,
                fwd: bool,
            ) -> Result<UniquePtr<FcShapeFixFace>>;
            fn init_face(self: &FcShapeFixFace, face: &TopoDS_Shape) -> Result<bool>;
            fn init_plane(
                self: &FcShapeFixFace,
                ox: f64,
                oy: f64,
                oz: f64,
                nx: f64,
                ny: f64,
                nz: f64,
                prec: f64,
                fwd: bool,
            ) -> Result<bool>;
            fn add(self: &FcShapeFixFace, wire: &TopoDS_Shape) -> Result<bool>;
            fn face(self: &FcShapeFixFace) -> Result<UniquePtr<TopoDS_Shape>>;
            fn result(self: &FcShapeFixFace) -> Result<UniquePtr<TopoDS_Shape>>;
            fn perform(self: &FcShapeFixFace) -> Result<bool>;
            fn clear_modes(self: &FcShapeFixFace);
            fn fix_orientation(self: &FcShapeFixFace) -> Result<bool>;
            fn fix_add_natural_bound(self: &FcShapeFixFace) -> Result<bool>;
            fn fix_missing_seam(self: &FcShapeFixFace) -> Result<bool>;
            fn fix_small_area_wire(self: &FcShapeFixFace, remove_small: bool) -> Result<bool>;
            fn fix_loop_wire(self: &FcShapeFixFace) -> Result<UniquePtr<FcShapeList>>;
            fn fix_intersecting_wires(self: &FcShapeFixFace) -> Result<bool>;
            fn fix_wires_two_coincident_edges(self: &FcShapeFixFace) -> Result<bool>;
            fn fix_periodic_degenerated(self: &FcShapeFixFace) -> Result<bool>;
            fn fix_wire_tool(self: &FcShapeFixFace) -> UniquePtr<FcShapeFixWire>;
            fn fix_wire_mode(self: &FcShapeFixFace) -> i32;
            fn set_fix_wire_mode(self: &FcShapeFixFace, value: i32);
            fn fix_orientation_mode(self: &FcShapeFixFace) -> i32;
            fn set_fix_orientation_mode(self: &FcShapeFixFace, value: i32);
            fn fix_add_natural_bound_mode(self: &FcShapeFixFace) -> i32;
            fn set_fix_add_natural_bound_mode(self: &FcShapeFixFace, value: i32);
            fn fix_missing_seam_mode(self: &FcShapeFixFace) -> i32;
            fn set_fix_missing_seam_mode(self: &FcShapeFixFace, value: i32);
            fn fix_small_area_wire_mode(self: &FcShapeFixFace) -> i32;
            fn set_fix_small_area_wire_mode(self: &FcShapeFixFace, value: i32);
            fn remove_small_area_face_mode(self: &FcShapeFixFace) -> i32;
            fn set_remove_small_area_face_mode(self: &FcShapeFixFace, value: i32);
            fn fix_intersecting_wires_mode(self: &FcShapeFixFace) -> i32;
            fn set_fix_intersecting_wires_mode(self: &FcShapeFixFace, value: i32);
            fn fix_loop_wires_mode(self: &FcShapeFixFace) -> i32;
            fn set_fix_loop_wires_mode(self: &FcShapeFixFace, value: i32);
            fn fix_split_face_mode(self: &FcShapeFixFace) -> i32;
            fn set_fix_split_face_mode(self: &FcShapeFixFace, value: i32);
            fn auto_correct_precision_mode(self: &FcShapeFixFace) -> i32;
            fn set_auto_correct_precision_mode(self: &FcShapeFixFace, value: i32);
            fn fix_periodic_degenerated_mode(self: &FcShapeFixFace) -> i32;
            fn set_fix_periodic_degenerated_mode(self: &FcShapeFixFace, value: i32);

            // --- Shell -----------------------------------------------------
            fn fc_shapefix_shell_new() -> UniquePtr<FcShapeFixShell>;
            fn fc_shapefix_shell_from_shell(
                shell: &TopoDS_Shape,
            ) -> Result<UniquePtr<FcShapeFixShell>>;
            fn init(self: &FcShapeFixShell, shell: &TopoDS_Shape) -> Result<bool>;
            fn perform(self: &FcShapeFixShell) -> Result<bool>;
            fn shape(self: &FcShapeFixShell) -> Result<UniquePtr<TopoDS_Shape>>;
            fn shell(self: &FcShapeFixShell) -> Result<UniquePtr<TopoDS_Shape>>;
            fn error_faces(self: &FcShapeFixShell) -> Result<UniquePtr<TopoDS_Shape>>;
            fn nb_shells(self: &FcShapeFixShell) -> i32;
            fn fix_face_tool(self: &FcShapeFixShell) -> UniquePtr<FcShapeFixFace>;
            fn fix_face_orientation(
                self: &FcShapeFixShell,
                shell: &TopoDS_Shape,
                multi_connex: bool,
                non_manifold: bool,
            ) -> Result<bool>;
            fn set_non_manifold_flag(self: &FcShapeFixShell, value: bool);
            fn fix_face_mode(self: &FcShapeFixShell) -> i32;
            fn set_fix_face_mode(self: &FcShapeFixShell, value: i32);
            fn fix_orientation_mode(self: &FcShapeFixShell) -> i32;
            fn set_fix_orientation_mode(self: &FcShapeFixShell, value: i32);

            // --- Solid -----------------------------------------------------
            fn fc_shapefix_solid_new() -> UniquePtr<FcShapeFixSolid>;
            fn fc_shapefix_solid_from_solid(
                solid: &TopoDS_Shape,
            ) -> Result<UniquePtr<FcShapeFixSolid>>;
            fn init(self: &FcShapeFixSolid, solid: &TopoDS_Shape) -> Result<bool>;
            fn perform(self: &FcShapeFixSolid) -> Result<bool>;
            fn shape(self: &FcShapeFixSolid) -> Result<UniquePtr<TopoDS_Shape>>;
            fn solid_from_shell(
                self: &FcShapeFixSolid,
                shell: &TopoDS_Shape,
            ) -> Result<UniquePtr<TopoDS_Shape>>;
            fn solid(self: &FcShapeFixSolid) -> Result<UniquePtr<TopoDS_Shape>>;
            fn fix_shell_tool(self: &FcShapeFixSolid) -> UniquePtr<FcShapeFixShell>;
            fn fix_shell_mode(self: &FcShapeFixSolid) -> i32;
            fn set_fix_shell_mode(self: &FcShapeFixSolid, value: i32);
            fn fix_shell_orientation_mode(self: &FcShapeFixSolid) -> i32;
            fn set_fix_shell_orientation_mode(self: &FcShapeFixSolid, value: i32);
            fn create_open_solid_mode(self: &FcShapeFixSolid) -> bool;
            fn set_create_open_solid_mode(self: &FcShapeFixSolid, value: bool);

            // --- Shape -----------------------------------------------------
            fn fc_shapefix_shape_new() -> UniquePtr<FcShapeFixShape>;
            fn fc_shapefix_shape_from_shape(
                shape: &TopoDS_Shape,
            ) -> Result<UniquePtr<FcShapeFixShape>>;
            fn init(self: &FcShapeFixShape, shape: &TopoDS_Shape) -> Result<bool>;
            fn perform(self: &FcShapeFixShape) -> Result<bool>;
            fn shape(self: &FcShapeFixShape) -> Result<UniquePtr<TopoDS_Shape>>;
            fn fix_solid_tool(self: &FcShapeFixShape) -> UniquePtr<FcShapeFixSolid>;
            fn fix_shell_tool(self: &FcShapeFixShape) -> UniquePtr<FcShapeFixShell>;
            fn fix_face_tool(self: &FcShapeFixShape) -> UniquePtr<FcShapeFixFace>;
            fn fix_wire_tool(self: &FcShapeFixShape) -> UniquePtr<FcShapeFixWire>;
            fn fix_edge_tool(self: &FcShapeFixShape) -> UniquePtr<FcShapeFixEdge>;
            fn fix_solid_mode(self: &FcShapeFixShape) -> i32;
            fn set_fix_solid_mode(self: &FcShapeFixShape, value: i32);
            fn fix_free_shell_mode(self: &FcShapeFixShape) -> i32;
            fn set_fix_free_shell_mode(self: &FcShapeFixShape, value: i32);
            fn fix_free_face_mode(self: &FcShapeFixShape) -> i32;
            fn set_fix_free_face_mode(self: &FcShapeFixShape, value: i32);
            fn fix_free_wire_mode(self: &FcShapeFixShape) -> i32;
            fn set_fix_free_wire_mode(self: &FcShapeFixShape, value: i32);
            fn fix_same_parameter_mode(self: &FcShapeFixShape) -> i32;
            fn set_fix_same_parameter_mode(self: &FcShapeFixShape, value: i32);
            fn fix_vertex_position_mode(self: &FcShapeFixShape) -> i32;
            fn set_fix_vertex_position_mode(self: &FcShapeFixShape, value: i32);
            fn fix_vertex_tol_mode(self: &FcShapeFixShape) -> i32;
            fn set_fix_vertex_tol_mode(self: &FcShapeFixShape, value: i32);

            // --- List ------------------------------------------------------
            fn is_ok(self: &FcShapeList) -> bool;
            fn size(self: &FcShapeList) -> usize;
            fn at(self: &FcShapeList, index: usize) -> &TopoDS_Shape;
    }
}

pub use ffi::*;
