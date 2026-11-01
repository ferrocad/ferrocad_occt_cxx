# ferrocad_part_cxx

Typed cxx bindings for the OCCT APIs that `opencascade-sys` does not expose.

## Boundary

This crate is **bindings only**:

- one function per OCCT call, named after the OCCT API;
- typed signatures (`Result<T>`, typed structs/enums), not flat `Vec<f64>`
  payloads or `nullptr`/`NaN` sentinels;
- `Standard_Failure` is caught and translated to `std::exception`, so cxx's
  `Result` shim delivers `Err` instead of terminating the process;
- no FerroCAD/FreeCAD semantics: no element naming, no history policy, no
  product decisions about what an operation should mean.

If a function needs to know what FreeCAD's `TopoShape` would do, or encodes
FerroCAD's ABI, it belongs in `ferrocad_occt` (Rust), not here.

## Status

`gtransform`, `ChFi2d` and `ShapeFix` all return typed `Result`s. The C++
boundary translates `Standard_Failure`; no sentinel values cross the bridge.

## Donation

The code here is written by FerroCAD and licensed `LGPL-2.1`, matching
`opencascade-sys` and this repository. It is offered for upstream donation: the
functions are generic OCCT bindings and can be merged into `opencascade-sys` (or
a sibling crate) without FerroCAD-specific behaviour. Ports of FreeCAD algorithms
are deliberately not accepted here; they stay in `ferrocad_occt`.
