pub use inner::*;

#[cxx::bridge]
mod inner {
    unsafe extern "C++" {
        include!("opencascade-sys/include/b_rep_extrema.hxx");

        type gp_Pnt = crate::gp::gp_Pnt;
        type TopoDS_Shape = crate::topo_ds::TopoDS_Shape;

        type BRepExtrema_DistShapeShape;
        #[cxx_name = "construct_unique"]
        pub fn BRepExtrema_DistShapeShape_new(
            first: &TopoDS_Shape,
            second: &TopoDS_Shape,
        ) -> UniquePtr<BRepExtrema_DistShapeShape>;
        pub fn IsDone(self: &BRepExtrema_DistShapeShape) -> bool;
        pub fn NbSolution(self: &BRepExtrema_DistShapeShape) -> i32;
        pub fn Value(self: &BRepExtrema_DistShapeShape) -> f64;
        pub fn BRepExtrema_DistShapeShape_point_on_shape1(
            s: &BRepExtrema_DistShapeShape,
            index: i32,
        ) -> UniquePtr<gp_Pnt>;
        pub fn BRepExtrema_DistShapeShape_point_on_shape2(
            s: &BRepExtrema_DistShapeShape,
            index: i32,
        ) -> UniquePtr<gp_Pnt>;
    }
}
