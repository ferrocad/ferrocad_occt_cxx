pub use inner::*;

#[cxx::bridge]
mod inner {
    unsafe extern "C++" {
        include!("opencascade-sys/include/g_prop.hxx");

        type gp_Ax1 = crate::gp::gp_Ax1;
        type gp_Pnt = crate::gp::gp_Pnt;
        type gp_Mat = crate::gp::gp_Mat;
        type gp_Vec = crate::gp::gp_Vec;

        type GProp_GProps;
        #[cxx_name = "construct_unique"]
        fn GProps_new() -> UniquePtr<GProp_GProps>;
        #[cxx_name = "construct_unique"]
        fn GProp_GProps_new_point(point: &gp_Pnt) -> UniquePtr<GProp_GProps>;
        fn Mass(self: &GProp_GProps) -> f64;
        fn StaticMoments(self: &GProp_GProps, lx: &mut f64, ly: &mut f64, lz: &mut f64);
        fn MomentOfInertia(self: &GProp_GProps, axis: &gp_Ax1) -> f64;
        fn RadiusOfGyration(self: &GProp_GProps, axis: &gp_Ax1) -> f64;
        fn GProp_GProps_CentreOfMass(props: &GProp_GProps) -> UniquePtr<gp_Pnt>;
        fn GProp_GProps_MatrixOfInertia(props: &GProp_GProps) -> UniquePtr<gp_Mat>;
        fn GProp_GProps_PrincipalProperties(
            props: &GProp_GProps,
        ) -> UniquePtr<GProp_PrincipalProps>;

        type GProp_PrincipalProps;
        fn Moments(self: &GProp_PrincipalProps, ixx: &mut f64, iyy: &mut f64, izz: &mut f64);
        fn FirstAxisOfInertia(self: &GProp_PrincipalProps) -> &gp_Vec;
        fn SecondAxisOfInertia(self: &GProp_PrincipalProps) -> &gp_Vec;
        fn ThirdAxisOfInertia(self: &GProp_PrincipalProps) -> &gp_Vec;
        fn RadiusOfGyration(
            self: &GProp_PrincipalProps,
            rxx: &mut f64,
            ryy: &mut f64,
            rzz: &mut f64,
        );
        fn HasSymmetryAxis(self: &GProp_PrincipalProps) -> bool;
        fn HasSymmetryPoint(self: &GProp_PrincipalProps) -> bool;
    }
}
