pub use inner::*;

#[cxx::bridge]
mod inner {
    unsafe extern "C++" {
        include!("opencascade-sys/include/t_col_std.hxx");

        type TColStd_Array1OfReal;
        #[cxx_name = "construct_unique"]
        pub fn TColStd_Array1OfReal_new(lower: i32, upper: i32) -> UniquePtr<TColStd_Array1OfReal>;
        pub fn Length(self: &TColStd_Array1OfReal) -> i32;
        pub fn TColStd_Array1OfReal_SetValue(
            array: Pin<&mut TColStd_Array1OfReal>,
            index: i32,
            value: f64,
        );
        pub fn TColStd_Array1OfReal_Value(array: &TColStd_Array1OfReal, index: i32) -> f64;

        type TColStd_Array1OfInteger;
        #[cxx_name = "construct_unique"]
        pub fn TColStd_Array1OfInteger_new(
            lower: i32,
            upper: i32,
        ) -> UniquePtr<TColStd_Array1OfInteger>;
        pub fn Length(self: &TColStd_Array1OfInteger) -> i32;
        pub fn TColStd_Array1OfInteger_SetValue(
            array: Pin<&mut TColStd_Array1OfInteger>,
            index: i32,
            value: i32,
        );
        pub fn TColStd_Array1OfInteger_Value(array: &TColStd_Array1OfInteger, index: i32) -> i32;

        type TColStd_Array2OfReal;
        #[cxx_name = "construct_unique"]
        pub fn TColStd_Array2OfReal_new(
            row_lower: i32,
            row_upper: i32,
            column_lower: i32,
            column_upper: i32,
        ) -> UniquePtr<TColStd_Array2OfReal>;
        pub fn TColStd_Array2OfReal_SetValue(
            array: Pin<&mut TColStd_Array2OfReal>,
            row: i32,
            column: i32,
            value: f64,
        );
        pub fn TColStd_Array2OfReal_Value(array: &TColStd_Array2OfReal, row: i32, column: i32) -> f64;
    }
}
