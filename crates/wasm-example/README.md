# wasm-example

An example of model code compiled to WASM. It implements the WIT contract in
[`../model-api/wit/model-api.wit`](../model-api/wit/model-api.wit) and depends only on
`model-api` and `glam` — no OCCT, no rendering.

Use [cargo watch](https://crates.io/crates/cargo-watch) to rebuild the module whenever
the model code is edited:

```sh
# From the project root
cargo watch --delay 0 -x "build -p wasm-example --release --target wasm32-unknown-unknown"
```

Build it once:

```sh
cargo build -p wasm-example --release --target wasm32-unknown-unknown
# target/wasm32-unknown-unknown/release/wasm_example.wasm
```

## Running it

The module needs a **host** that implements the WIT imports (the OCCT-backed
constructors and queries) and runs the component. This fork does not ship one:
upstream's `viewer` was removed with the other demo crates. FerroCAD or any other app
can be the host by implementing `model-api/wit/model-api.wit`.

The host is what links OCCT; the wasm module stays kernel-free and small, so model code
can be rebuilt and swapped without recompiling the kernel.
