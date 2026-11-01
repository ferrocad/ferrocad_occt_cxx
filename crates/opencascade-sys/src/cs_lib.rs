pub use inner::*;

#[cxx::bridge]
mod inner {
    #[repr(u32)]
    #[derive(Debug)]
    pub enum CSLib_NormalStatus {
        CSLib_Singular,
        CSLib_Defined,
        CSLib_InfinityOfSolutions,
        CSLib_D1NuIsNull,
        CSLib_D1NvIsNull,
        CSLib_D1NIsNull,
        CSLib_D1NuNvRatioIsNull,
        CSLib_D1NvNuRatioIsNull,
        CSLib_D1NuIsParallelD1Nv,
    }

    unsafe extern "C++" {
        include!("opencascade-sys/include/cs_lib.hxx");

        type gp_Vec = crate::gp::gp_Vec;
        type gp_Dir = crate::gp::gp_Dir;

        type CSLib_NormalStatus;

        pub fn CSLib_Normal(
            d1u: &gp_Vec,
            d1v: &gp_Vec,
            d2u: &gp_Vec,
            d2v: &gp_Vec,
            duv: &gp_Vec,
            tolerance: f64,
            status: &mut CSLib_NormalStatus,
        ) -> Result<UniquePtr<gp_Dir>>;
    }
}
