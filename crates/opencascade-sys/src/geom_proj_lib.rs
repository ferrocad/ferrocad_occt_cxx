pub use inner::*;

#[cxx::bridge]
mod inner {
    unsafe extern "C++" {
        include!("opencascade-sys/include/geom_proj_lib.hxx");

        type Handle_Geom_Curve = crate::geom::Handle_Geom_Curve;
        type Handle_Geom_Surface = crate::geom::Handle_Geom_Surface;
        type Handle_Geom2d_Curve = crate::geom2d::Handle_Geom2d_Curve;

        pub fn GeomProjLib_Curve2d(
            curve: &Handle_Geom_Curve,
            first: f64,
            last: f64,
            surface: &Handle_Geom_Surface,
        ) -> Result<UniquePtr<Handle_Geom2d_Curve>>;
    }
}
