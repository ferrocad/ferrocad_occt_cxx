pub use inner::*;

#[cxx::bridge]
mod inner {
    unsafe extern "C++" {
        include!("opencascade-sys/include/b_rep.hxx");

        type TopoDS_Builder = crate::topo_ds::TopoDS_Builder;
        type gp_Pnt = crate::gp::gp_Pnt;
        type TopoDS_Shape = crate::topo_ds::TopoDS_Shape;
        type TopoDS_Face = crate::topo_ds::TopoDS_Face;
        type TopoDS_Edge = crate::topo_ds::TopoDS_Edge;
        type TopoDS_Vertex = crate::topo_ds::TopoDS_Vertex;
        type TopoDS_Wire = crate::topo_ds::TopoDS_Wire;
        type Handle_Geom_Surface = crate::geom::Handle_Geom_Surface;
        type Handle_Geom_Curve = crate::geom::Handle_Geom_Curve;
        type Handle_Geom2d_Curve = crate::geom2d::Handle_Geom2d_Curve;
        type Handle_Poly_Triangulation = crate::poly::Handle_Poly_Triangulation;
        type TopLoc_Location = crate::top_loc::TopLoc_Location;

        type BRep_Builder;
        #[cxx_name = "construct_unique"]
        pub fn BRep_Builder_new() -> UniquePtr<BRep_Builder>;
        pub fn BRep_Builder_upcast_to_topods_builder(builder: &BRep_Builder) -> &TopoDS_Builder;
        pub fn BRep_Builder_Transfert(
            builder: &BRep_Builder,
            edge_in: &TopoDS_Edge,
            edge_out: &TopoDS_Edge,
        );
        pub fn BRep_Builder_Range(
            builder: &BRep_Builder,
            edge: &TopoDS_Edge,
            first: f64,
            last: f64,
        );
        pub fn BRep_Builder_MakeFace(
            builder: &BRep_Builder,
            face: Pin<&mut TopoDS_Face>,
            surface: &Handle_Geom_Surface,
            tolerance: f64,
        );
        pub fn BRep_Builder_MakeWire(builder: &BRep_Builder, wire: Pin<&mut TopoDS_Wire>);
        pub fn BRep_Builder_UpdateEdge(
            builder: &BRep_Builder,
            edge: &TopoDS_Edge,
            curve: &Handle_Geom2d_Curve,
            surface: &Handle_Geom_Surface,
            location: &TopLoc_Location,
            tolerance: f64,
        );

        type BRep_Tool;
        #[Self = "BRep_Tool"]
        pub fn Degenerated(edge: &TopoDS_Edge) -> bool;
        #[Self = "BRep_Tool"]
        pub fn Range(edge: &TopoDS_Edge, first: &mut f64, last: &mut f64);
        pub fn BRep_Tool_IsClosed_shape(shape: &TopoDS_Shape) -> bool;
        pub fn BRep_Tool_IsClosed_edge_face(edge: &TopoDS_Edge, face: &TopoDS_Face) -> bool;
        pub fn BRep_Tool_Tolerance_vertex(vertex: &TopoDS_Vertex) -> f64;
        pub fn BRep_Tool_Tolerance_edge(edge: &TopoDS_Edge) -> f64;
        pub fn BRep_Tool_Tolerance_face(face: &TopoDS_Face) -> f64;
        pub fn BRep_Tool_Parameter_edge(vertex: &TopoDS_Vertex, edge: &TopoDS_Edge) -> f64;
        pub fn BRep_Tool_Surface(face: &TopoDS_Face) -> UniquePtr<Handle_Geom_Surface>;
        pub fn BRep_Tool_Curve(
            edge: &TopoDS_Edge,
            first: &mut f64,
            last: &mut f64,
        ) -> UniquePtr<Handle_Geom_Curve>;
        pub fn BRep_Tool_Pnt(vertex: &TopoDS_Vertex) -> UniquePtr<gp_Pnt>;
        pub fn BRep_Tool_Triangulation(
            face: &TopoDS_Face,
            location: Pin<&mut TopLoc_Location>,
        ) -> UniquePtr<Handle_Poly_Triangulation>;
        pub fn BRep_Tool_Curve_Location(
            edge: &TopoDS_Edge,
            location: Pin<&mut TopLoc_Location>,
            first: &mut f64,
            last: &mut f64,
        ) -> UniquePtr<Handle_Geom_Curve>;
        pub fn BRep_Tool_CurveOnSurface(
            edge: &TopoDS_Edge,
            curve: Pin<&mut Handle_Geom2d_Curve>,
            surface: Pin<&mut Handle_Geom_Surface>,
            location: Pin<&mut TopLoc_Location>,
            first: &mut f64,
            last: &mut f64,
        );
        /// `BRep_Tool::Tolerance` for any of the tolerance-bearing shape types
        /// (vertex, edge, face); raises for other types.
        pub fn BRep_Tool_Tolerance(shape: &TopoDS_Shape) -> Result<f64>;
    }
}
