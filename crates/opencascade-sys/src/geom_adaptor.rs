pub use inner::*;

#[cxx::bridge]
mod inner {
    unsafe extern "C++" {
        include!("opencascade-sys/include/geom_adaptor.hxx");

        type Handle_Geom_Surface = crate::geom::Handle_Geom_Surface;
        type Handle_Geom_Curve = crate::geom::Handle_Geom_Curve;
        type gp_Pln = crate::gp::gp_Pln;

        type GeomAdaptor_Surface;
        pub fn GeomAdaptor_Surface_new(
            surface: &Handle_Geom_Surface,
        ) -> Result<UniquePtr<GeomAdaptor_Surface>>;
        pub fn GeomAdaptor_Surface_Plane(adaptor: &GeomAdaptor_Surface) -> Result<UniquePtr<gp_Pln>>;

        type GeomAdaptor_Curve;
        pub fn GeomAdaptor_Curve_Curve(adaptor: &GeomAdaptor_Curve) -> UniquePtr<Handle_Geom_Curve>;
    }
}
