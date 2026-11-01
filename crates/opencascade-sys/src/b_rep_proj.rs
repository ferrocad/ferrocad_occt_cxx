pub use inner::*;

#[cxx::bridge]
mod inner {
    unsafe extern "C++" {
        include!("opencascade-sys/include/b_rep_proj.hxx");

        type TopoDS_Shape = crate::topo_ds::TopoDS_Shape;
        type TopoDS_Compound = crate::topo_ds::TopoDS_Compound;
        type gp_Dir = crate::gp::gp_Dir;
        type gp_Pnt = crate::gp::gp_Pnt;

        type BRepProj_Projection;
        pub fn BRepProj_Projection_dir_new(
            tool: &TopoDS_Shape,
            target: &TopoDS_Shape,
            dir: &gp_Dir,
        ) -> Result<UniquePtr<BRepProj_Projection>>;
        pub fn BRepProj_Projection_pnt_new(
            tool: &TopoDS_Shape,
            target: &TopoDS_Shape,
            pnt: &gp_Pnt,
        ) -> Result<UniquePtr<BRepProj_Projection>>;
        pub fn IsDone(self: &BRepProj_Projection) -> bool;
        pub fn BRepProj_Projection_Shape(
            projection: &BRepProj_Projection,
        ) -> UniquePtr<TopoDS_Compound>;
    }
}
