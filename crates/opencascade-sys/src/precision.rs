//! OCCT's `Precision` package: the default tolerances the kernel and its
//! algorithms are written against.

#[cxx::bridge]
mod inner {
    unsafe extern "C++" {
        include!("opencascade-sys/include/precision.hxx");

        type Precision;

        /// `Precision::Confusion()`, the default linear tolerance (1e-7).
        #[Self = "Precision"]
        fn Confusion() -> f64;

        /// `Precision::IsInfinite()`: true when the magnitude reaches the
        /// kernel's "infinite" threshold.
        #[Self = "Precision"]
        fn IsInfinite(value: f64) -> bool;
    }
}

pub use inner::*;
