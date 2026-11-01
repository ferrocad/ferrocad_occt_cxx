use cxx::UniquePtr;
use opencascade_sys as ffi;

use ffi::top_abs::TopAbs_ShapeEnum;
use ffi::topo_ds::{TopoDS, TopoDS_Shape};

/// The first *direct* child of `shape` (`TopoDS_Iterator` order).
fn first_child(shape: &TopoDS_Shape) -> UniquePtr<TopoDS_Shape> {
    let mut iterator = ffi::topo_ds::TopoDS_Iterator_new(shape);
    if iterator.More() {
        let child = ffi::topo_ds::TopoDS_Shape_to_owned(iterator.Value());
        iterator.pin_mut().Next();
        child
    } else {
        UniquePtr::null()
    }
}

fn non_null(shape: UniquePtr<TopoDS_Shape>) -> UniquePtr<TopoDS_Shape> {
    assert!(!shape.is_null(), "expected a shape");
    shape
}

fn make_box(size: f64) -> UniquePtr<TopoDS_Shape> {
    let origin = ffi::gp::new_point(0.0, 0.0, 0.0);
    let mut make = ffi::b_rep_prim_api::BRepPrimAPI_MakeBox_new(&origin, size, size, size);
    let mut copier = ffi::b_rep_builder_api::BRepBuilderAPI_Copy_new(make.pin_mut().Shape(), true, false);
    assert!(copier.IsDone(), "a box copy");
    ffi::topo_ds::TopoDS_Shape_to_owned(copier.pin_mut().Shape())
}

/// `Build()` raises `Standard_Failure` when an added edge belongs to another
/// shape. Crossing cxx's `noexcept` shim with it would abort the process; the
/// C++ helper catches it and delivers it as `Result::Err`.
#[test]
fn a_throwing_build_is_reported_instead_of_terminating() {
    let cube = make_box(10.0);
    let other = make_box(5.0);

    // solid -> shell -> face -> wire -> edge; the edge is not part of `cube`.
    let shell = non_null(first_child(&other));
    let face = non_null(first_child(&shell));
    let wire = non_null(first_child(&face));
    let edge = non_null(first_child(&wire));
    assert_eq!(
        edge.as_ref().unwrap().ShapeType(),
        TopAbs_ShapeEnum::TopAbs_EDGE
    );

    let mut op = ffi::b_rep_fillet_api::BRepFilletAPI_MakeFillet_new(&cube);
    op.pin_mut().add_edge(1.0, TopoDS::Edge(edge.as_ref().unwrap()));

    match ffi::b_rep_fillet_api::BRepFilletAPI_MakeFillet_build(op.pin_mut()) {
        Err(e) => assert!(!e.what().is_empty(), "the failure carries OCCT's message"),
        Ok(()) => panic!("a foreign edge must be reported, not built"),
    }
}

#[test]
fn explore_and_predicates_answer_for_a_box() {
    let cube = make_box(10.0);
    // `IsClosed` is the shape's own `Closed` flag. A solid does not carry a
    // meaningful one - a host policy asks its shells - so this must not be
    // read as "the box is open".
    assert!(!ffi::b_rep::BRep_Tool_IsClosed_shape(&cube));

    let mut faces = ffi::top_tools::new_indexed_map_of_shape();
    let mut xp = ffi::top_exp::TopExp_Explorer_new_avoid(
        &cube,
        TopAbs_ShapeEnum::TopAbs_FACE,
        TopAbs_ShapeEnum::TopAbs_SHAPE,
    );
    while xp.More() {
        faces.pin_mut().Add(xp.Current());
        xp.pin_mut().Next();
    }
    assert_eq!(faces.Extent(), 6, "a box has six faces");

    let face = faces.FindKey(1);
    assert!(!ffi::b_rep::BRep_Tool_IsClosed_shape(face), "a plane is not closed");
    assert!(
        ffi::b_rep::BRep_Tool_Tolerance_face(TopoDS::Face(face)) > 0.0,
        "a face carries a tolerance"
    );
}
