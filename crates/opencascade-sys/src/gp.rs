pub use inner::*;

#[cxx::bridge]
mod inner {
    unsafe extern "C++" {
        include!("opencascade-sys/include/gp.hxx");

        type gp;
        #[Self = "gp"]
        pub fn OX() -> &'static gp_Ax1;
        #[Self = "gp"]
        pub fn OY() -> &'static gp_Ax1;
        #[Self = "gp"]
        pub fn OZ() -> &'static gp_Ax1;
        #[Self = "gp"]
        pub fn DZ() -> &'static gp_Dir;
        #[Self = "gp"]
        pub fn XOY() -> &'static gp_Ax2;

        type gp_Pnt;
        #[cxx_name = "construct_unique"]
        pub fn new_point(x: f64, y: f64, z: f64) -> UniquePtr<gp_Pnt>;
        pub fn X(self: &gp_Pnt) -> f64;
        pub fn Y(self: &gp_Pnt) -> f64;
        pub fn Z(self: &gp_Pnt) -> f64;
        pub fn Distance(self: &gp_Pnt, other: &gp_Pnt) -> f64;
        pub fn Transform(self: Pin<&mut gp_Pnt>, transform: &gp_Trsf);

        type gp_Pnt2d;
        #[cxx_name = "construct_unique"]
        pub fn new_point_2d(x: f64, y: f64) -> UniquePtr<gp_Pnt2d>;
        pub fn X(self: &gp_Pnt2d) -> f64;
        pub fn Y(self: &gp_Pnt2d) -> f64;
        pub fn Distance(self: &gp_Pnt2d, other: &gp_Pnt2d) -> f64;

        type gp_Vec;
        #[cxx_name = "construct_unique"]
        pub fn new_vec(x: f64, y: f64, z: f64) -> UniquePtr<gp_Vec>;
        pub fn X(self: &gp_Vec) -> f64;
        pub fn Y(self: &gp_Vec) -> f64;
        pub fn Z(self: &gp_Vec) -> f64;
        pub fn Magnitude(self: &gp_Vec) -> f64;
        pub fn Normalize(self: Pin<&mut gp_Vec>);
        pub fn gp_Vec_Crossed(left: &gp_Vec, right: &gp_Vec) -> UniquePtr<gp_Vec>;

        type gp_Lin;
        #[cxx_name = "construct_unique"]
        pub fn gp_Lin_new(point: &gp_Pnt, dir: &gp_Dir) -> UniquePtr<gp_Lin>;

        type gp_Circ;
        #[cxx_name = "construct_unique"]
        pub fn gp_Circ_new(axis: &gp_Ax2, radius: f64) -> UniquePtr<gp_Circ>;

        type gp_Elips;
        pub fn gp_Elips_new(
            axis: &gp_Ax2,
            major_radius: f64,
            minor_radius: f64,
        ) -> Result<UniquePtr<gp_Elips>>;

        type gp_Hypr;
        pub fn gp_Hypr_new(
            axis: &gp_Ax2,
            major_radius: f64,
            minor_radius: f64,
        ) -> Result<UniquePtr<gp_Hypr>>;

        type gp_Parab;
        pub fn gp_Parab_new(axis: &gp_Ax2, focal: f64) -> Result<UniquePtr<gp_Parab>>;

        type gp_Pln;
        #[cxx_name = "construct_unique"]
        pub fn gp_Pln_new(point: &gp_Pnt, dir: &gp_Dir) -> UniquePtr<gp_Pln>;
        pub fn gp_Pln_new_abcd(a: f64, b: f64, c: f64, d: f64) -> Result<UniquePtr<gp_Pln>>;
        pub fn gp_Pln_new_frame(frame: &gp_Ax3) -> Result<UniquePtr<gp_Pln>>;

        type gp_Ax1;
        #[cxx_name = "construct_unique"]
        pub fn gp_Ax1_new(origin: &gp_Pnt, main_dir: &gp_Dir) -> UniquePtr<gp_Ax1>;

        type gp_Ax2;
        #[cxx_name = "construct_unique"]
        pub fn gp_Ax2_new(origin: &gp_Pnt, main_dir: &gp_Dir) -> UniquePtr<gp_Ax2>;
        pub fn gp_Ax2_new3(
            origin: &gp_Pnt,
            main_dir: &gp_Dir,
            x_dir: &gp_Dir,
        ) -> Result<UniquePtr<gp_Ax2>>;

        type gp_Ax3;
        #[cxx_name = "construct_unique"]
        pub fn gp_Ax3_from_gp_Ax2(axis: &gp_Ax2) -> UniquePtr<gp_Ax3>;
        pub fn gp_Ax3_new3(
            origin: &gp_Pnt,
            main_dir: &gp_Dir,
            x_dir: &gp_Dir,
        ) -> Result<UniquePtr<gp_Ax3>>;
        pub fn Location(self: &gp_Ax3) -> &gp_Pnt;
        pub fn Direction(self: &gp_Ax3) -> &gp_Dir;
        pub fn XDirection(self: &gp_Ax3) -> &gp_Dir;
        pub fn YDirection(self: &gp_Ax3) -> &gp_Dir;
        pub fn Direct(self: &gp_Ax3) -> bool;

        type gp_Dir2d;
        #[cxx_name = "construct_unique"]
        pub fn gp_Dir2d_new(x: f64, y: f64) -> UniquePtr<gp_Dir2d>;

        type gp_Ax2d;
        #[cxx_name = "construct_unique"]
        pub fn gp_Ax2d_new(point: &gp_Pnt2d, dir: &gp_Dir2d) -> UniquePtr<gp_Ax2d>;

        type gp_Dir;
        #[cxx_name = "construct_unique"]
        pub fn gp_Dir_new(x: f64, y: f64, z: f64) -> UniquePtr<gp_Dir>;
        pub fn Transform(self: Pin<&mut gp_Dir>, transform: &gp_Trsf);
        pub fn X(self: &gp_Dir) -> f64;
        pub fn Y(self: &gp_Dir) -> f64;
        pub fn Z(self: &gp_Dir) -> f64;

        type gp_Mat;
        #[cxx_name = "construct_unique"]
        pub fn gp_Mat_new() -> UniquePtr<gp_Mat>;
        pub fn gp_Mat_Value(matrix: &gp_Mat, row: i32, col: i32) -> f64;

        type gp_Trsf;
        #[cxx_name = "construct_unique"]
        pub fn new_transform() -> UniquePtr<gp_Trsf>;
        #[rust_name = "set_mirror_axis"]
        pub fn SetMirror(self: Pin<&mut gp_Trsf>, axis: &gp_Ax1);
        pub fn SetRotation(self: Pin<&mut gp_Trsf>, axis: &gp_Ax1, angle: f64);
        pub fn SetScale(self: Pin<&mut gp_Trsf>, point: &gp_Pnt, scale: f64);
        pub fn SetTranslation(self: Pin<&mut gp_Trsf>, point1: &gp_Pnt, point2: &gp_Pnt);
        pub fn Value(self: &gp_Trsf, the_row: i32, the_col: i32) -> f64;
        #[cxx_name = "SetTranslationPart"]
        pub fn set_translation_vec(self: Pin<&mut gp_Trsf>, translation: &gp_Vec);
        #[allow(clippy::too_many_arguments)]
        pub fn gp_Trsf_SetValues(
            transform: Pin<&mut gp_Trsf>,
            a11: f64,
            a12: f64,
            a13: f64,
            a14: f64,
            a21: f64,
            a22: f64,
            a23: f64,
            a24: f64,
            a31: f64,
            a32: f64,
            a33: f64,
            a34: f64,
        ) -> Result<()>;

        type gp_GTrsf;
        #[cxx_name = "construct_unique"]
        pub fn new_gp_GTrsf() -> UniquePtr<gp_GTrsf>;
        pub fn SetValue(self: Pin<&mut gp_GTrsf>, the_row: i32, the_col: i32, the_value: f64);
        pub fn Value(self: &gp_GTrsf, the_row: i32, the_col: i32) -> f64;
    }
}
