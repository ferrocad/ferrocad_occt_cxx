//! Typed bindings for OCCT topology queries, fillet/chamfer building and
//! fillet/chamfer lineage.
//!
//! These are the calls `opencascade-sys` 0.3 does not bridge. They are bindings
//! only: application-level answers built *on top* of them (for example FreeCAD's
//! `TopoShape::isClosed`, or its default shape tolerance) live in the caller.

#[cxx::bridge]
mod ffi {
    unsafe extern "C++" {
        include!("ferrocad_part_cxx/include/topology.hxx");

        type BRepFilletAPI_MakeFillet = opencascade_sys::b_rep_fillet_api::BRepFilletAPI_MakeFillet;
        type BRepFilletAPI_MakeChamfer =
            opencascade_sys::b_rep_fillet_api::BRepFilletAPI_MakeChamfer;
        type TopoDS_Shape = opencascade_sys::topo_ds::TopoDS_Shape;
        type TopoDS_Edge = opencascade_sys::topo_ds::TopoDS_Edge;
        type TopoDS_Face = opencascade_sys::topo_ds::TopoDS_Face;
        type TopoDS_Vertex = opencascade_sys::topo_ds::TopoDS_Vertex;
        type TopAbs_ShapeEnum = opencascade_sys::top_abs::TopAbs_ShapeEnum;
        type TopTools_IndexedMapOfShape = opencascade_sys::top_tools::TopTools_IndexedMapOfShape;
        type TopTools_IndexedDataMapOfShapeListOfShape =
            opencascade_sys::top_tools::TopTools_IndexedDataMapOfShapeListOfShape;
        type TopTools_ListOfShape = opencascade_sys::top_tools::TopTools_ListOfShape;

        // --- shape identity ---------------------------------------------------
        /// A deep copy with a new TShape (`BRepBuilderAPI_Copy`), or null.
        fn fc_copy_shape(shape: &TopoDS_Shape) -> UniquePtr<TopoDS_Shape>;

        /// A hash consistent with `IsSame` (TShape + location, orientation ignored).
        fn fc_shape_hash(shape: &TopoDS_Shape, upper: u64) -> u64;

        // --- ancestor / element lists -----------------------------------------
        /// `TopTools_ListOfShape::Size`.
        fn fc_list_size(list: &TopTools_ListOfShape) -> i32;

        /// The `index`-th shape in the list (1-based).
        fn fc_list_value<'a>(list: &'a TopTools_ListOfShape, index: i32) -> &'a TopoDS_Shape;

        /// Like `fc_indexed_map_find_index`, but ignores orientation (`IsSame`).
        fn fc_indexed_map_find_index_same(
            map: &TopTools_IndexedMapOfShape,
            shape: &TopoDS_Shape,
        ) -> i32;

        /// Like `fc_indexed_map_find_index_same`, for the ancestor data map.
        fn fc_data_map_find_index_same(
            map: &TopTools_IndexedDataMapOfShapeListOfShape,
            shape: &TopoDS_Shape,
        ) -> i32;

        // --- fillet / chamfer -------------------------------------------------
        /// The two-distance chamfer form.
        fn fc_chamfer_add_asym(
            op: Pin<&mut BRepFilletAPI_MakeChamfer>,
            distance1: f64,
            distance2: f64,
            edge: &TopoDS_Edge,
            face: &TopoDS_Face,
        );

        /// `Build()` wrapped so an OCCT exception is reported instead of
        /// crossing cxx's `noexcept` shim. True on success; on failure
        /// `message` holds OCCT's own text.
        fn fc_fillet_build(
            op: Pin<&mut BRepFilletAPI_MakeFillet>,
            message: &mut String,
        ) -> bool;
        fn fc_chamfer_build(
            op: Pin<&mut BRepFilletAPI_MakeChamfer>,
            message: &mut String,
        ) -> bool;

        fn fc_fillet_modified(
            op: Pin<&mut BRepFilletAPI_MakeFillet>,
            shape: &TopoDS_Shape,
            out: Pin<&mut TopTools_IndexedMapOfShape>,
        );
        fn fc_fillet_generated(
            op: Pin<&mut BRepFilletAPI_MakeFillet>,
            shape: &TopoDS_Shape,
            out: Pin<&mut TopTools_IndexedMapOfShape>,
        );
        fn fc_fillet_is_deleted(
            op: Pin<&mut BRepFilletAPI_MakeFillet>,
            shape: &TopoDS_Shape,
        ) -> bool;

        fn fc_chamfer_modified(
            op: Pin<&mut BRepFilletAPI_MakeChamfer>,
            shape: &TopoDS_Shape,
            out: Pin<&mut TopTools_IndexedMapOfShape>,
        );
        fn fc_chamfer_generated(
            op: Pin<&mut BRepFilletAPI_MakeChamfer>,
            shape: &TopoDS_Shape,
            out: Pin<&mut TopTools_IndexedMapOfShape>,
        );
        fn fc_chamfer_is_deleted(
            op: Pin<&mut BRepFilletAPI_MakeChamfer>,
            shape: &TopoDS_Shape,
        ) -> bool;

        /// Two unit tangents at the edges' shared vertex (six numbers), or empty.
        fn fc_edge_tangents(edge1: &TopoDS_Edge, edge2: &TopoDS_Edge, out: &mut Vec<f64>);

        // --- shape queries ----------------------------------------------------
        /// `BRep_Tool::Degenerated`.
        fn fc_edge_degenerated(shape: &TopoDS_Shape) -> bool;

        /// `BRep_Tool::IsClosed(edge, face)`: the edge is a seam of the face.
        fn fc_edge_is_seam(edge: &TopoDS_Shape, face: &TopoDS_Shape) -> bool;

        /// The edge's curve parameter range (`BRep_Tool::Range`).
        fn fc_edge_range(shape: &TopoDS_Shape, first: &mut f64, last: &mut f64);

        /// The face's UV bounds (`BRepTools::UVBounds`).
        fn fc_face_uv_bounds(
            shape: &TopoDS_Shape,
            u0: &mut f64,
            u1: &mut f64,
            v0: &mut f64,
            v1: &mut f64,
        );

        /// The number of direct children (`TopoDS_Iterator`).
        fn fc_direct_child_count(shape: &TopoDS_Shape) -> i32;

        // --- closedness and tolerance -----------------------------------------
        /// `BRep_Tool::IsClosed(shape)`: the shape's own `Closed` flag.
        fn fc_shape_is_closed(shape: &TopoDS_Shape) -> bool;

        /// `BRep_Tool::Tolerance` of a vertex.
        fn fc_vertex_tolerance(vertex: &TopoDS_Vertex) -> f64;

        /// `BRep_Tool::Tolerance` of an edge.
        fn fc_edge_tolerance(edge: &TopoDS_Edge) -> f64;

        /// `BRep_Tool::Tolerance` of a face.
        fn fc_face_tolerance(face: &TopoDS_Face) -> f64;

        /// Sub-shapes of type `to_find` that are not contained in a `to_avoid`
        /// sub-shape (`TopExp_Explorer`). `TopAbs_SHAPE` as `to_avoid` explores
        /// the whole subtree.
        fn fc_explore(
            shape: &TopoDS_Shape,
            to_find: TopAbs_ShapeEnum,
            to_avoid: TopAbs_ShapeEnum,
            out: Pin<&mut TopTools_IndexedMapOfShape>,
        );

        /// The minimum distance between two shapes and the closest point on each
        /// (`BRepExtrema_DistShapeShape`). False when there is no solution.
        fn fc_dist_to_shape(
            first: &TopoDS_Shape,
            second: &TopoDS_Shape,
            distance: &mut f64,
            first_x: &mut f64,
            first_y: &mut f64,
            first_z: &mut f64,
            second_x: &mut f64,
            second_y: &mut f64,
            second_z: &mut f64,
        ) -> bool;

        // --- geometry queries -------------------------------------------------
        /// The point of an edge at curve parameter `parameter`
        /// (`BRepAdaptor_Curve::Value`).
        fn fc_edge_value(
            shape: &TopoDS_Shape,
            parameter: f64,
            x: &mut f64,
            y: &mut f64,
            z: &mut f64,
        ) -> bool;

        /// The point of a face at surface parameters `(u, v)`
        /// (`BRepAdaptor_Surface::Value`).
        fn fc_face_value(
            shape: &TopoDS_Shape,
            u: f64,
            v: f64,
            x: &mut f64,
            y: &mut f64,
            z: &mut f64,
        ) -> bool;

        /// The face's backing surface frame, tagged by kind (`BRepAdaptor_Surface`
        /// for a plane, cylinder or sphere); empty for any other surface.
        fn fc_face_surface_data(shape: &TopoDS_Shape, out: &mut Vec<f64>);
    }
}

pub use ffi::*;

#[cfg(test)]
mod tests {
    use super::{fc_copy_shape, fc_fillet_build};
    use super::{fc_explore, fc_face_tolerance, fc_shape_is_closed};
    use crate::history::fc_shape_child;
    use cxx::UniquePtr;
    use opencascade_sys as sys;
    use sys::topo_ds::{TopoDS, TopoDS_Shape};

    fn non_null(shape: UniquePtr<TopoDS_Shape>) -> UniquePtr<TopoDS_Shape> {
        assert!(!shape.is_null(), "expected a shape");
        shape
    }

    fn make_box(size: f64) -> UniquePtr<TopoDS_Shape> {
        let origin = sys::gp::new_point(0.0, 0.0, 0.0);
        let mut make = sys::b_rep_prim_api::BRepPrimAPI_MakeBox_new(&origin, size, size, size);
        non_null(fc_copy_shape(make.pin_mut().Shape()))
    }

    /// `Build()` raises `Standard_Failure` when an added edge belongs to another
    /// shape. Crossing cxx's `noexcept` shim with it would abort the process; the
    /// wrapper catches it and reports it instead.
    #[test]
    fn a_throwing_build_is_reported_instead_of_terminating() {
        let cube = make_box(10.0);
        let other = make_box(5.0);

        // solid -> shell -> face -> wire -> edge; the edge is not part of `cube`.
        let shell = non_null(fc_shape_child(&other, 1));
        let face = non_null(fc_shape_child(&shell, 1));
        let wire = non_null(fc_shape_child(&face, 1));
        let edge = non_null(fc_shape_child(&wire, 1));
        assert_eq!(
            edge.as_ref().unwrap().ShapeType(),
            sys::top_abs::TopAbs_ShapeEnum::TopAbs_EDGE
        );

        let mut op = sys::b_rep_fillet_api::BRepFilletAPI_MakeFillet_new(&cube);
        op.pin_mut().add_edge(1.0, TopoDS::Edge(edge.as_ref().unwrap()));

        let mut message = String::new();
        assert!(
            !fc_fillet_build(op.pin_mut(), &mut message),
            "a foreign edge must be reported, not built"
        );
        assert!(!message.is_empty(), "the failure carries OCCT's message");
    }

    #[test]
    fn explore_and_predicates_answer_for_a_box() {
        let cube = make_box(10.0);
        // `IsClosed` is the shape's own `Closed` flag. A solid does not carry a
        // meaningful one - a host policy asks its shells - so this must not be
        // read as "the box is open".
        assert!(!fc_shape_is_closed(&cube));

        let mut faces = sys::top_tools::new_indexed_map_of_shape();
        fc_explore(
            &cube,
            sys::top_abs::TopAbs_ShapeEnum::TopAbs_FACE,
            sys::top_abs::TopAbs_ShapeEnum::TopAbs_SHAPE,
            faces.pin_mut(),
        );
        assert_eq!(faces.Extent(), 6, "a box has six faces");

        let face = faces.FindKey(1);
        assert!(!fc_shape_is_closed(face), "a plane is not closed");
        assert!(fc_face_tolerance(TopoDS::Face(face)) > 0.0, "a face carries a tolerance");
    }
}
