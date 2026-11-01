//! The surface and solid operations bindings (partial spheres, variable fillets,
//! offsets, hollows, helices, pipe shells, the thread loft).

#[cxx::bridge]
mod ffi {
    unsafe extern "C++" {
        include!("ferrocad_part_cxx/include/surface_ops.hxx");

        // Reuse the crate's opaque types. cxx shares these across bridges by path.
        type TopoDS_Shape = opencascade_sys::topo_ds::TopoDS_Shape;
        type TopTools_ListOfShape = opencascade_sys::top_tools::TopTools_ListOfShape;

        /// A sphere slice (see the header for the `u`/`v` conventions).
        fn fc_make_sphere_slice(
            radius: f64,
            x: f64,
            y: f64,
            z: f64,
            u1: f64,
            u2: f64,
            v1: f64,
            v2: f64,
        ) -> UniquePtr<TopoDS_Shape>;

        /// A fillet with a per-edge radius law (`Add(start, end, edge)`).
        fn fc_fillet_variable(
            shape: &TopoDS_Shape,
            edges: &TopTools_ListOfShape,
            start_radii: &[f64],
            end_radii: &[f64],
        ) -> UniquePtr<TopoDS_Shape>;

        /// `BRepOffsetAPI_MakeOffset`, optionally filled into the band face.
        fn fc_offset2d(
            shape: &TopoDS_Shape,
            distance: f64,
            kind: i32,
            fill: bool,
            open_result: bool,
        ) -> UniquePtr<TopoDS_Shape>;

        /// A solid from an outer shell plus cavity shells.
        fn fc_make_hollow_solid(shells: &TopTools_ListOfShape) -> UniquePtr<TopoDS_Shape>;

        /// An edge on the analytic cylinder/cone whose pcurve is the helix line.
        fn fc_make_helix_edge(
            pitch: f64,
            height: f64,
            radius: f64,
            angle: f64,
            left_handed: bool,
        ) -> UniquePtr<TopoDS_Shape>;

        /// `BRepOffsetAPI_MakePipeShell` with `SetMode`/`SetTransitionMode`.
        fn fc_make_pipe_shell(
            spine: &TopoDS_Shape,
            profiles: &TopTools_ListOfShape,
            solid: bool,
            frenet: bool,
        ) -> UniquePtr<TopoDS_Shape>;

        /// Upstream's two-cylinder thread loft (`TopoShape::makeThread`).
        fn fc_make_thread(
            pitch: f64,
            depth: f64,
            height: f64,
            radius: f64,
        ) -> UniquePtr<TopoDS_Shape>;

        /// The point and unit tangent at the start of a spine (`[p, t]`).
        fn fc_spine_start_frame(spine: &TopoDS_Shape) -> Vec<f64>;

        /// The direction of a straight edge (`[d]`), honouring its orientation.
        fn fc_edge_line_direction(edge: &TopoDS_Shape) -> Vec<f64>;

        /// The normal of the plane a shape lies on (`[n]`).
        fn fc_shape_plane_normal(shape: &TopoDS_Shape) -> Vec<f64>;

        /// A cylinder slice (`BRepPrimAPI_MakeCylinder` with an angular sweep),
        /// or null. `angle` is in radians.
        fn fc_make_cylinder_slice(
            radius: f64,
            height: f64,
            x: f64,
            y: f64,
            z: f64,
            dx: f64,
            dy: f64,
            dz: f64,
            angle: f64,
        ) -> UniquePtr<TopoDS_Shape>;
    }
}

pub use ffi::*;
