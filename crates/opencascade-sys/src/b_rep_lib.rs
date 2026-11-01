pub use inner::*;

#[cxx::bridge]
mod inner {
    unsafe extern "C++" {
        include!("opencascade-sys/include/b_rep_lib.hxx");

        type TopoDS_Shape = crate::topo_ds::TopoDS_Shape;
        type TopoDS_Edge = crate::topo_ds::TopoDS_Edge;
        type TopoDS_Face = crate::topo_ds::TopoDS_Face;
        type TopoDS_Solid = crate::topo_ds::TopoDS_Solid;
        type Handle_Geom_Surface = crate::geom::Handle_Geom_Surface;
        type Handle_Poly_Triangulation = crate::poly::Handle_Poly_Triangulation;
        type TopTools_ListOfShape = crate::top_tools::TopTools_ListOfShape;
        type GeomAbs_Shape = crate::geom_api::GeomAbs_Shape;

        type BRepLib;
        #[Self = "BRepLib"]
        pub fn BuildCurves3d(shape: &TopoDS_Shape) -> bool;
        pub fn BRepLib_BuildCurves3d_full(
            shape: &TopoDS_Shape,
            tol: f64,
            continuity: GeomAbs_Shape,
            max_degree: i32,
            max_segment: i32,
        ) -> Result<bool>;
        pub fn BRepLib_BuildPCurveForEdgesOnPlane(
            edges: &TopTools_ListOfShape,
            face: &TopoDS_Face,
        ) -> Result<()>;
        pub fn BRepLib_SameRange(edge: &TopoDS_Edge, tolerance: f64) -> Result<()>;
        #[Self = "BRepLib"]
        pub fn OrientClosedSolid(solid: Pin<&mut TopoDS_Solid>) -> bool;

        pub fn BRepLib_ToolTriangulatedShape_ComputeNormals(face: &TopoDS_Face, triangulation: &Handle_Poly_Triangulation);

        type BRepLib_FindSurface;
        #[cxx_name = "construct_unique"]
        pub fn BRepLib_FindSurface_new(
            shape: &TopoDS_Shape,
            tolerance: f64,
            only_plane: bool,
        ) -> UniquePtr<BRepLib_FindSurface>;
        pub fn Found(self: &BRepLib_FindSurface) -> bool;
        pub fn BRepLib_FindSurface_Surface(
            finder: &BRepLib_FindSurface,
        ) -> UniquePtr<Handle_Geom_Surface>;
    }
}
