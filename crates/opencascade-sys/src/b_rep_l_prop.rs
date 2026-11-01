pub use inner::*;

#[cxx::bridge]
mod inner {
    unsafe extern "C++" {
        include!("opencascade-sys/include/b_rep_l_prop.hxx");

        type BRepAdaptor_Curve = crate::b_rep_adaptor::BRepAdaptor_Curve;
        type gp_Dir = crate::gp::gp_Dir;
        type gp_Vec = crate::gp::gp_Vec;

        type BRepLProp_CLProps;
        pub fn BRepLProp_CLProps_new(
            curve: &BRepAdaptor_Curve,
            u: f64,
            n: i32,
            resolution: f64,
        ) -> Result<UniquePtr<BRepLProp_CLProps>>;
        pub fn IsTangentDefined(self: Pin<&mut BRepLProp_CLProps>) -> bool;
        pub fn CLProps_Normal(props: Pin<&mut BRepLProp_CLProps>) -> Result<UniquePtr<gp_Dir>>;
        pub fn CLProps_D1(props: Pin<&mut BRepLProp_CLProps>) -> Result<UniquePtr<gp_Vec>>;
        pub fn CLProps_D2(props: Pin<&mut BRepLProp_CLProps>) -> Result<UniquePtr<gp_Vec>>;
        pub fn CLProps_D3(props: Pin<&mut BRepLProp_CLProps>) -> Result<UniquePtr<gp_Vec>>;
        pub fn CLProps_Curvature(props: Pin<&mut BRepLProp_CLProps>) -> Result<f64>;
    }
}
