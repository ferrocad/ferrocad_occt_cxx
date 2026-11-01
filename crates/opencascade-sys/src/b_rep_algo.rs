pub use inner::*;

#[cxx::bridge]
mod inner {
    unsafe extern "C++" {
        include!("opencascade-sys/include/b_rep_algo.hxx");

        type TopoDS_Shape = crate::topo_ds::TopoDS_Shape;
        type TopTools_ListOfShape = crate::top_tools::TopTools_ListOfShape;
        type GeomAbs_Shape = crate::geom_api::GeomAbs_Shape;

        type BRepAlgo_NormalProjection;
        pub fn BRepAlgo_NormalProjection_new(
            target: &TopoDS_Shape,
        ) -> Result<UniquePtr<BRepAlgo_NormalProjection>>;
        pub fn Add(self: Pin<&mut BRepAlgo_NormalProjection>, shape: &TopoDS_Shape);
        pub fn BRepAlgo_NormalProjection_Compute3d(
            projection: Pin<&mut BRepAlgo_NormalProjection>,
            with_3d: bool,
        ) -> Result<()>;
        pub fn SetLimit(self: Pin<&mut BRepAlgo_NormalProjection>, face_boundaries: bool);
        pub fn SetParams(
            self: Pin<&mut BRepAlgo_NormalProjection>,
            tol_3d: f64,
            tol_2d: f64,
            continuity: GeomAbs_Shape,
            max_degree: i32,
            max_segment: i32,
        );
        pub fn BRepAlgo_NormalProjection_Build(
            projection: Pin<&mut BRepAlgo_NormalProjection>,
        ) -> Result<()>;
        pub fn IsDone(self: &BRepAlgo_NormalProjection) -> bool;
        pub fn Projection(self: &BRepAlgo_NormalProjection) -> &TopoDS_Shape;

        type BRepAlgo_Image;
        pub fn HasImage(self: &BRepAlgo_Image, shape: &TopoDS_Shape) -> bool;
        pub fn Image(self: &BRepAlgo_Image, shape: &TopoDS_Shape) -> &TopTools_ListOfShape;
    }
}
