//! Typed bindings for OCCT's `ChFi2d` package.
//!
//! Every fallible method returns a cxx `Result`; OCCT's `Standard_Failure` is
//! translated in C++ (`include/chfi2d.hxx`). FerroCAD's `Option`/`Part.OCCError`
//! mapping lives in `ferrocad_occt::chfi2d`.

#[cxx::bridge]
mod ffi {
    unsafe extern "C++" {
        include!("ferrocad_part_cxx/include/chfi2d.hxx");

        type TopoDS_Shape = opencascade_sys::topo_ds::TopoDS_Shape;

        type ChFi2dEdgeTriple;
        type ChFi2dFilletAlgo;
        type ChFi2dAnaFilletAlgo;
        type ChFi2dChamferApi;

        fn chfi2d_fillet_algo_new() -> UniquePtr<ChFi2dFilletAlgo>;
        fn init_wire(
            self: &ChFi2dFilletAlgo,
            wire: &TopoDS_Shape,
            ox: f64,
            oy: f64,
            oz: f64,
            nx: f64,
            ny: f64,
            nz: f64,
        ) -> Result<()>;
        fn init_edges(
            self: &ChFi2dFilletAlgo,
            edge1: &TopoDS_Shape,
            edge2: &TopoDS_Shape,
            ox: f64,
            oy: f64,
            oz: f64,
            nx: f64,
            ny: f64,
            nz: f64,
        ) -> Result<()>;
        fn perform(self: &ChFi2dFilletAlgo, radius: f64) -> Result<bool>;
        fn nb_results(self: &ChFi2dFilletAlgo, x: f64, y: f64, z: f64) -> Result<i32>;
        fn result(
            self: &ChFi2dFilletAlgo,
            x: f64,
            y: f64,
            z: f64,
            solution: i32,
        ) -> Result<UniquePtr<ChFi2dEdgeTriple>>;

        fn chfi2d_ana_fillet_algo_new() -> UniquePtr<ChFi2dAnaFilletAlgo>;
        fn init_wire(
            self: &ChFi2dAnaFilletAlgo,
            wire: &TopoDS_Shape,
            ox: f64,
            oy: f64,
            oz: f64,
            nx: f64,
            ny: f64,
            nz: f64,
        ) -> Result<()>;
        fn init_edges(
            self: &ChFi2dAnaFilletAlgo,
            edge1: &TopoDS_Shape,
            edge2: &TopoDS_Shape,
            ox: f64,
            oy: f64,
            oz: f64,
            nx: f64,
            ny: f64,
            nz: f64,
        ) -> Result<()>;
        fn perform(self: &ChFi2dAnaFilletAlgo, radius: f64) -> Result<bool>;
        fn result(self: &ChFi2dAnaFilletAlgo) -> Result<UniquePtr<ChFi2dEdgeTriple>>;

        fn chfi2d_chamfer_api_new() -> UniquePtr<ChFi2dChamferApi>;
        fn init_wire(self: &ChFi2dChamferApi, wire: &TopoDS_Shape) -> Result<()>;
        fn init_edges(
            self: &ChFi2dChamferApi,
            edge1: &TopoDS_Shape,
            edge2: &TopoDS_Shape,
        ) -> Result<()>;
        fn perform(self: &ChFi2dChamferApi) -> Result<bool>;
        fn result(
            self: &ChFi2dChamferApi,
            length1: f64,
            length2: f64,
        ) -> Result<UniquePtr<ChFi2dEdgeTriple>>;

        fn first_shape(self: &ChFi2dEdgeTriple) -> &TopoDS_Shape;
        fn second_shape(self: &ChFi2dEdgeTriple) -> &TopoDS_Shape;
        fn third_shape(self: &ChFi2dEdgeTriple) -> &TopoDS_Shape;
        fn first_is_null(self: &ChFi2dEdgeTriple) -> bool;
        fn second_is_null(self: &ChFi2dEdgeTriple) -> bool;
        fn third_is_null(self: &ChFi2dEdgeTriple) -> bool;
    }
}

pub use ffi::*;
