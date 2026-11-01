pub use inner::*;

#[cxx::bridge]
mod inner {
    unsafe extern "C++" {
        include!("opencascade-sys/include/bspl_clib.hxx");

        type TColStd_Array1OfReal = crate::t_col_std::TColStd_Array1OfReal;

        pub fn BSplCLib_Reparametrize(
            first: f64,
            last: f64,
            knots: Pin<&mut TColStd_Array1OfReal>,
        ) -> Result<()>;
    }
}
