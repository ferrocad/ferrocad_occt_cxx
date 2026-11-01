pub use inner::*;

#[cxx::bridge]
mod inner {
    unsafe extern "C++" {
        include!("opencascade-sys/include/b_rep_top_adaptor.hxx");

        type TopoDS_Face = crate::topo_ds::TopoDS_Face;
        type TopAbs_State = crate::b_rep_class::TopAbs_State;

        pub fn BRepTopAdaptor_FClass2d_Perform(
            face: &TopoDS_Face,
            u: f64,
            v: f64,
        ) -> Result<TopAbs_State>;
    }
}
