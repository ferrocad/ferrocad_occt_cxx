//! Typed bindings for OCCT boolean-operation history, element maps, shape
//! structure and in-memory BREP persistence.
//!
//! These are the calls `opencascade-sys` 0.3 does not bridge. They are bindings
//! only: the reuse policy of an operation object (non-destructive mode, fuzzy
//! values, how a host application walks a compound) lives in the caller.

#[cxx::bridge]
mod ffi {
    unsafe extern "C++" {
        include!("ferrocad_part_cxx/include/history.hxx");

        type BRepAlgoAPI_Fuse = opencascade_sys::b_rep_algo_api::BRepAlgoAPI_Fuse;
        type BRepAlgoAPI_Cut = opencascade_sys::b_rep_algo_api::BRepAlgoAPI_Cut;
        type BRepAlgoAPI_Common = opencascade_sys::b_rep_algo_api::BRepAlgoAPI_Common;
        type TopoDS_Shape = opencascade_sys::topo_ds::TopoDS_Shape;
        type TopTools_IndexedMapOfShape = opencascade_sys::top_tools::TopTools_IndexedMapOfShape;
        type TopTools_ListOfShape = opencascade_sys::top_tools::TopTools_ListOfShape;

        /// `TopTools_IndexedMapOfShape::FindIndex`, which the crate does not bridge.
        fn fc_indexed_map_find_index(map: &TopTools_IndexedMapOfShape, shape: &TopoDS_Shape)
        -> i32;

        // --- boolean-operation history ---------------------------------------
        fn fc_brep_fuse_modified(
            op: Pin<&mut BRepAlgoAPI_Fuse>,
            shape: &TopoDS_Shape,
            out: Pin<&mut TopTools_IndexedMapOfShape>,
        );
        fn fc_brep_fuse_generated(
            op: Pin<&mut BRepAlgoAPI_Fuse>,
            shape: &TopoDS_Shape,
            out: Pin<&mut TopTools_IndexedMapOfShape>,
        );
        fn fc_brep_fuse_is_deleted(op: Pin<&mut BRepAlgoAPI_Fuse>, shape: &TopoDS_Shape) -> bool;

        fn fc_brep_cut_modified(
            op: Pin<&mut BRepAlgoAPI_Cut>,
            shape: &TopoDS_Shape,
            out: Pin<&mut TopTools_IndexedMapOfShape>,
        );
        fn fc_brep_cut_generated(
            op: Pin<&mut BRepAlgoAPI_Cut>,
            shape: &TopoDS_Shape,
            out: Pin<&mut TopTools_IndexedMapOfShape>,
        );
        fn fc_brep_cut_is_deleted(op: Pin<&mut BRepAlgoAPI_Cut>, shape: &TopoDS_Shape) -> bool;

        fn fc_brep_common_modified(
            op: Pin<&mut BRepAlgoAPI_Common>,
            shape: &TopoDS_Shape,
            out: Pin<&mut TopTools_IndexedMapOfShape>,
        );
        fn fc_brep_common_generated(
            op: Pin<&mut BRepAlgoAPI_Common>,
            shape: &TopoDS_Shape,
            out: Pin<&mut TopTools_IndexedMapOfShape>,
        );
        fn fc_brep_common_is_deleted(
            op: Pin<&mut BRepAlgoAPI_Common>,
            shape: &TopoDS_Shape,
        ) -> bool;

        /// A default-constructed cut operation that can be reconfigured and
        /// rebuilt several times (the crate's constructor runs the operation).
        fn fc_cut_new_op() -> UniquePtr<BRepAlgoAPI_Cut>;

        /// Switch a cut operation between `BOPAlgo_CUT` and `BOPAlgo_FUSE`.
        fn fc_cut_set_operation(op: Pin<&mut BRepAlgoAPI_Cut>, fuse: bool);

        /// Install the argument/tool lists (`SetArguments`/`SetTools`).
        fn fc_cut_configure(
            op: Pin<&mut BRepAlgoAPI_Cut>,
            arguments: &TopTools_ListOfShape,
            tools: &TopTools_ListOfShape,
        );

        /// `Build()` with a default progress range.
        fn fc_cut_build(op: Pin<&mut BRepAlgoAPI_Cut>);

        // --- shape structure --------------------------------------------------
        /// The number of *direct* children (`TopoDS_Iterator`).
        fn fc_shape_child_count(shape: &TopoDS_Shape) -> i32;

        /// The `index`-th (1-based) direct child, or null.
        fn fc_shape_child(shape: &TopoDS_Shape, index: i32) -> UniquePtr<TopoDS_Shape>;

        // --- BREP persistence -------------------------------------------------
        /// Serialise a shape to BREP bytes (in memory; the crate only does files).
        fn fc_brep_write(shape: &TopoDS_Shape, out: &mut Vec<u8>);
        /// Read a shape from BREP bytes; null on failure.
        fn fc_brep_read(data: &[u8]) -> UniquePtr<TopoDS_Shape>;
    }
}

pub use ffi::*;

#[cfg(test)]
mod tests {
    use super::{fc_brep_read, fc_brep_write, fc_shape_child_count};
    use crate::topology::fc_copy_shape;
    use cxx::UniquePtr;
    use opencascade_sys as sys;
    use sys::topo_ds::TopoDS_Shape;

    fn non_null(shape: UniquePtr<TopoDS_Shape>) -> UniquePtr<TopoDS_Shape> {
        assert!(!shape.is_null(), "expected a shape");
        shape
    }

    fn make_box(size: f64) -> UniquePtr<TopoDS_Shape> {
        let origin = sys::gp::new_point(0.0, 0.0, 0.0);
        let mut make = sys::b_rep_prim_api::BRepPrimAPI_MakeBox_new(&origin, size, size, size);
        non_null(fc_copy_shape(make.pin_mut().Shape()))
    }

    #[test]
    fn brep_bytes_round_trip() {
        let cube = make_box(10.0);
        // `fc_shape_child_count` counts *direct* children, which for a box solid
        // is its single shell.
        let direct_children = fc_shape_child_count(&cube);
        assert!(direct_children > 0, "a box has at least one child");

        let mut bytes = Vec::new();
        fc_brep_write(&cube, &mut bytes);
        assert!(!bytes.is_empty(), "BREP serialisation produces bytes");

        let read = non_null(fc_brep_read(&bytes));
        assert_eq!(fc_shape_child_count(&read), direct_children);
    }
}
