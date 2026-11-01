//! Typed cxx bindings for OCCT calls that `opencascade-sys` does not expose.
//!
//! This crate is the C++ boundary and is **bindings only**: one function per
//! OCCT call, named after the OCCT API, with typed results and exception
//! translation. It contains no FerroCAD/FreeCAD semantics - no element naming,
//! no history policy, no product decisions about what a shape operation should
//! mean. Those stay in `ferrocad_occt` (Rust).
//!
//! That separation is deliberate: these bindings are generic OCCT access and can
//! be donated to `opencascade-sys` (or merged into a sibling crate) without
//! carrying FerroCAD-specific behaviour.
//!
//! `ops` and `surface_ops` are the exception, and explicitly staged: they were
//! moved out of `ferrocad_occt` so that crate could drop C++ entirely, and some
//! of their entries still mirror a FreeCAD `TopoShape` method or carry flat
//! `Vec<f64>` payloads. Splitting those is tracked in ferrocad/ferrocad#2.

pub mod chfi2d;
pub mod ops;
pub mod shapefix;
pub mod surface_ops;
