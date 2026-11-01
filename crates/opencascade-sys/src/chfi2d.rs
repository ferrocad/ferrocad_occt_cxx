//! Typed bindings for OCCT's `ChFi2d` package.
//!
//! Every fallible method returns a cxx `Result`; OCCT's `Standard_Failure` (which
//! does not derive from `std::exception` on OCCT 7.x) is translated to
//! `std::runtime_error` in `include/chfi2d.hxx`.
//!
//! # `Result` edge triple
//!
//! OCCT's `Result` methods return the new fillet/chamfer edge plus two
//! caller-modified trimmed input edges. Rather than the FerroCAD-specific
//! `ChFi2dEdgeTriple` ABI, each edge is exposed as a separate typed
//! `TopoDS_Edge` value: the new edge is returned as an owned
//! `UniquePtr<TopoDS_Edge>`, and the two trimmed edges are written to
//! caller-provided `TopoDS_Edge` out-parameters.

pub use inner::*;

#[cxx::bridge]
mod inner {
    unsafe extern "C++" {
        include!("opencascade-sys/include/chfi2d.hxx");

        type gp_Pln = crate::gp::gp_Pln;
        type gp_Pnt = crate::gp::gp_Pnt;
        type TopoDS_Edge = crate::topo_ds::TopoDS_Edge;
        type TopoDS_Wire = crate::topo_ds::TopoDS_Wire;

        type ChFi2d_FilletAlgo;
        #[cxx_name = "construct_unique"]
        pub fn ChFi2d_FilletAlgo_new() -> UniquePtr<ChFi2d_FilletAlgo>;
        pub fn ChFi2d_FilletAlgo_Init(
            algo: Pin<&mut ChFi2d_FilletAlgo>,
            wire: &TopoDS_Wire,
            plane: &gp_Pln,
        ) -> Result<()>;
        pub fn ChFi2d_FilletAlgo_Init_edges(
            algo: Pin<&mut ChFi2d_FilletAlgo>,
            edge1: &TopoDS_Edge,
            edge2: &TopoDS_Edge,
            plane: &gp_Pln,
        ) -> Result<()>;
        pub fn ChFi2d_FilletAlgo_Perform(
            algo: Pin<&mut ChFi2d_FilletAlgo>,
            radius: f64,
        ) -> Result<bool>;
        pub fn ChFi2d_FilletAlgo_NbResults(
            algo: Pin<&mut ChFi2d_FilletAlgo>,
            point: &gp_Pnt,
        ) -> Result<i32>;
        pub fn ChFi2d_FilletAlgo_Result(
            algo: Pin<&mut ChFi2d_FilletAlgo>,
            point: &gp_Pnt,
            solution: i32,
            edge1: Pin<&mut TopoDS_Edge>,
            edge2: Pin<&mut TopoDS_Edge>,
        ) -> Result<UniquePtr<TopoDS_Edge>>;

        type ChFi2d_AnaFilletAlgo;
        #[cxx_name = "construct_unique"]
        pub fn ChFi2d_AnaFilletAlgo_new() -> UniquePtr<ChFi2d_AnaFilletAlgo>;
        pub fn ChFi2d_AnaFilletAlgo_Init(
            algo: Pin<&mut ChFi2d_AnaFilletAlgo>,
            wire: &TopoDS_Wire,
            plane: &gp_Pln,
        ) -> Result<()>;
        pub fn ChFi2d_AnaFilletAlgo_Init_edges(
            algo: Pin<&mut ChFi2d_AnaFilletAlgo>,
            edge1: &TopoDS_Edge,
            edge2: &TopoDS_Edge,
            plane: &gp_Pln,
        ) -> Result<()>;
        pub fn ChFi2d_AnaFilletAlgo_Perform(
            algo: Pin<&mut ChFi2d_AnaFilletAlgo>,
            radius: f64,
        ) -> Result<bool>;
        pub fn ChFi2d_AnaFilletAlgo_Result(
            algo: Pin<&mut ChFi2d_AnaFilletAlgo>,
            edge1: Pin<&mut TopoDS_Edge>,
            edge2: Pin<&mut TopoDS_Edge>,
        ) -> Result<UniquePtr<TopoDS_Edge>>;

        type ChFi2d_ChamferAPI;
        #[cxx_name = "construct_unique"]
        pub fn ChFi2d_ChamferAPI_new() -> UniquePtr<ChFi2d_ChamferAPI>;
        pub fn ChFi2d_ChamferAPI_Init(
            algo: Pin<&mut ChFi2d_ChamferAPI>,
            wire: &TopoDS_Wire,
        ) -> Result<()>;
        pub fn ChFi2d_ChamferAPI_Init_edges(
            algo: Pin<&mut ChFi2d_ChamferAPI>,
            edge1: &TopoDS_Edge,
            edge2: &TopoDS_Edge,
        ) -> Result<()>;
        pub fn ChFi2d_ChamferAPI_Perform(
            algo: Pin<&mut ChFi2d_ChamferAPI>,
        ) -> Result<bool>;
        pub fn ChFi2d_ChamferAPI_Result(
            algo: Pin<&mut ChFi2d_ChamferAPI>,
            length1: f64,
            length2: f64,
            edge1: Pin<&mut TopoDS_Edge>,
            edge2: Pin<&mut TopoDS_Edge>,
        ) -> Result<UniquePtr<TopoDS_Edge>>;
    }
}
