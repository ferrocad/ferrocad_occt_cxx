pub use inner::*;

#[cxx::bridge]
mod inner {
    #[repr(u32)]
    #[derive(Debug)]
    pub enum TopAbs_State {
        TopAbs_IN,
        TopAbs_OUT,
        TopAbs_ON,
        TopAbs_UNKNOWN,
    }

    unsafe extern "C++" {
        include!("opencascade-sys/include/b_rep_class.hxx");

        type TopoDS_Shape = crate::topo_ds::TopoDS_Shape;
        type TopoDS_Face = crate::topo_ds::TopoDS_Face;

        type TopAbs_State;

        type SolidClassifierState;
        pub fn State(self: &SolidClassifierState) -> TopAbs_State;
        pub fn IsOnAFace(self: &SolidClassifierState) -> bool;

        pub fn BRepClass3d_SolidClassifier_Perform(
            shape: &TopoDS_Shape,
            x: f64,
            y: f64,
            z: f64,
            tol: f64,
        ) -> Result<UniquePtr<SolidClassifierState>>;

        pub fn BRepClass_FaceClassifier_State(
            face: &TopoDS_Face,
            u: f64,
            v: f64,
            tol: f64,
        ) -> Result<TopAbs_State>;
    }
}
