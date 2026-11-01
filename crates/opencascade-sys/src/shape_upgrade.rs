pub use inner::*;

#[cxx::bridge]
mod inner {
    unsafe extern "C++" {
        include!("opencascade-sys/include/shape_upgrade.hxx");

        type TopoDS_Shape = crate::topo_ds::TopoDS_Shape;

        type ShapeUpgrade_UnifySameDomain;
        #[cxx_name = "construct_unique"]
        pub fn UnifySameDomain_new(
            shape: &TopoDS_Shape,
            unify_edges: bool,
            unify_faces: bool,
            concat_b_splines: bool,
        ) -> UniquePtr<ShapeUpgrade_UnifySameDomain>;
        #[cxx_name = "AllowInternalEdges"]
        pub fn allow_internal_edges(self: Pin<&mut ShapeUpgrade_UnifySameDomain>, allow: bool);
        #[cxx_name = "Build"]
        pub fn build(self: Pin<&mut ShapeUpgrade_UnifySameDomain>);
        #[cxx_name = "Shape"]
        pub fn shape(self: &ShapeUpgrade_UnifySameDomain) -> &TopoDS_Shape;

        type ShapeUpgrade_RemoveInternalWires;
        pub fn RemoveInternalWires_new(
            shape: &TopoDS_Shape,
        ) -> Result<UniquePtr<ShapeUpgrade_RemoveInternalWires>>;
        pub fn RemoveInternalWires_set_min_area(
            fix: Pin<&mut ShapeUpgrade_RemoveInternalWires>,
            value: f64,
        );
        pub fn RemoveInternalWires_Perform(
            fix: Pin<&mut ShapeUpgrade_RemoveInternalWires>,
        ) -> Result<bool>;
        pub fn RemoveInternalWires_GetResult(
            fix: &ShapeUpgrade_RemoveInternalWires,
        ) -> Result<UniquePtr<TopoDS_Shape>>;

        pub fn ShapeUpgrade_ShellSewing_ApplySewing(
            shape: &TopoDS_Shape,
        ) -> Result<UniquePtr<TopoDS_Shape>>;
    }
}
