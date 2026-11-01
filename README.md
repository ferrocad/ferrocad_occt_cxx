# ferrocad_occt_cxx

> **Fork.** This is FerroCAD's fork of
> [`bschwind/opencascade-rs`](https://github.com/bschwind/opencascade-rs).
> It keeps `crates/opencascade-sys` (package `ferrocad_occt_cxx`, library
> `opencascade_sys` — the crate FerroCAD builds) and the WASM model boundary
> (`crates/model-api` + `crates/wasm-example`). Upstream's high-level API, viewer,
> KiCad parser and demo models are removed; see "Fork status".

Rust bindings to [OpenCascade](https://dev.opencascade.org). The code is currently a major work in progress.

I currently work a full-time job and work on this in my spare time, so please adjust timing expectations accordingly :)

## Fork status

- **Base:** upstream `v0.3` (`32758df`), with the OCCT 8 compatibility work.
- **Keeps:**
  - `crates/opencascade-sys` (package `ferrocad_occt_cxx`, library
    `opencascade_sys`) — the only crate FerroCAD builds.
  - `crates/model-api` (the WIT contract) and `crates/wasm-example` (a model
    compiled to `wasm32-unknown-unknown`) — the WASM path.
  - `crates/occt-sys` — the optional `builtin` static build of OCCT.
- **Removed:** upstream's high-level `opencascade` API, the `viewer` demo, the
  KiCad parser and the example models. FerroCAD does not use them, and the WASM
  path is the model/WIT boundary rather than the demo host. They remain in the
  git history if they are ever needed again.
- **OCCT versions:** 7.8.1 (the CI default) and 8.0.1.
- **Rebasing:** add upstream as a remote and cherry-pick the fork commits onto a
  new upstream tag; fork tags are `v0.3.0-ferrocad.N`.
- **License:** LGPL-2.1, unchanged. Upstream authors retain copyright; the
  modifications are recorded in the git history and here.

The rest of this README is upstream's.

## Major Goals

*(Upstream's goals; this fork ships the binding layer and the WASM boundary.)*

* Define 3D CAD models suitable for 3D printing or machining, in ergonomic Rust code
* Code-first approach, but allow use of a GUI where it makes sense (2D sketches)
* Support fillets, chamfers, lofts, surface filling, pipes, extrusions, revolutions, etc.
* Support quick compile times for faster iterations
* Ability to import/export STEP files, STL files, SVG, DXF, KiCAD files, and hopefully more!
* Easy to install the viewer app (provide pre-built binaries for major platforms)
* Easy to create and use user-authored libraries (via crates.io) for quick and easy code-sharing
* Pretty visualizations of created parts
* Ability to specify assemblies of parts, and constraints between assembled parts

## Rationale

This project was born out of me designing [my own keyboard](https://github.com/bschwind/key-ripper) and wanting to make a 3D-printed or CNCed aluminum case for it. In typical over-engineering fashion, I didn't want to just use Fusion360 and call it a day. I wanted a fully parameterized, fully open-source, code-based approach so I can easily make changes, and store the model code in version control. I also want to be fairly confident I can build these models any time in the future given I have a C++/Rust toolchain available.

So I researched what kernels are out there, learned that OpenCascade is one of the few open-source B-Rep (boundary representation) kernels available, and started writing bindings to it with cxx.rs to see if usage of the kernel is feasible. Turns out it is!

### Why Rust?

At this point I'm most comfortable with Rust, so most tools I build will be with Rust. I also don't find any joy in creating my own language or forcing people to learn one I created. Rust is a far better language than I could ever make myself, and contains pretty much every facility I would want for defining 3D models in code. Ultimately it's a hobby project and when you run a hobby project, you get to pick whatever you want :)

There are other benefits:

* Easy to install the Rust toolchain
* Strong type system can inform you what you can do with say, a `Wire` or a `Shape`
* Great generated documentation
* Good cross-platform support
* Excellent library ecosystem on crates.io, making parts sharing a breeze
* High level Rust can be ergonomic, with iterators, closures, operator overloading, and enums
* Rust's unique (`&mut T`) and shared (`&T`) references and function type signatures inform you when an operation modifies a shape vs. creating a new one

## Dependencies

* Rust Toolchain (https://rustup.rs/)
* CMake (https://cmake.org/)
* A C++ compiler with C++11 support

## Building

* The `OCCT` codebase is included as a git submodule. Clone the repo with the `--recursive` flag, or use `git submodule update --init` to fetch the submodule.
* `cargo build --release`

### Using a pre-installed OpenCASCADE (the default)

The default build links the shared OpenCASCADE libraries that CMake finds. Point it at a
prefix with `OpenCASCADE_DIR` (the directory containing `OpenCASCADEConfig.cmake`) and
`OCCT_INCLUDE_DIR`; a micromamba/conda prefix works:

```sh
micromamba create -y -p .occt/prefix -c conda-forge occt=7.8.1
export OpenCASCADE_DIR="$PWD/.occt/prefix/lib/cmake/opencascade"
export OCCT_INCLUDE_DIR="$PWD/.occt/prefix/include/opencascade"
export LD_LIBRARY_PATH="$PWD/.occt/prefix/lib"
cargo build
```

This is the fast path, it is what FerroCAD uses, and it keeps OCCT a shared library
(one kernel on disk, updated independently of the binary).

### Building OCCT from source (`builtin`)

If no OCCT is installed, enable the vendored build. It compiles the whole kernel from
the `occt-sys` submodule — minutes to build, and statically linked:

```sh
cargo build --features builtin
```

Downstream crates opt in the same way: enable the `builtin` feature on
`ferrocad_occt_cxx`.

NOTE: If you installed `OCCT` manually you may need specify the path to it via the `DEP_OCCT_ROOT` environment variable. The specified root directory usually contains `include` and `lib` directories.

## Run Examples

* `cargo run --release --example bottle`

The program will output `bottle.stl` in the current working directory.

### Lower Level

There are low level examples which are more or less directly calling OpenCascade functions, such as the classic OpenCascade [bottle](./crates/opencascade-sys/examples/bottle.rs) example, or a [simpler](./crates/opencascade-sys/examples/simple.rs) one.

## WASM models

The WASM path is the model/WIT boundary, not a bundled viewer:

- [`crates/model-api`](./crates/model-api) defines the WIT contract and the
  `Model` trait, so a model can be compiled to `wasm32-unknown-unknown`.
- [`crates/wasm-example`](./crates/wasm-example) is such a model.

```sh
cargo build -p wasm-example --release --target wasm32-unknown-unknown
```

A host supplies the OCCT-backed imports and runs the module. This fork does not
ship one (upstream's `viewer` was removed); FerroCAD or any other app can be that
host by implementing the WIT interface.

### The kernel itself in wasm

The bindings can also target `wasm32-unknown-unknown` against a prebuilt OCCT. Set
`OCCT_WASM_ROOT` to the extracted
[`occt-8_0_1_rev3-wasm32_unknown_unknown`](https://github.com/lzpel/cadrum/releases/download/occt-8_0_1_rev3/occt-8_0_1_rev3-wasm32_unknown_unknown.tar.gz)
tarball and build inside
`ghcr.io/lzpel/cross-wasm32-unknown-unknown`, which carries the wasi-sdk toolchain
whose wasm-EH encoding matches it:

```sh
docker run --rm -v "$PWD":/work -w /work \
  -e OCCT_WASM_ROOT=/work/.occt-wasm/occt-8_0_1_rev3-wasm32_unknown_unknown \
  ghcr.io/lzpel/cross-wasm32-unknown-unknown \
  cargo check -p ferrocad_occt_cxx --target wasm32-unknown-unknown
```

The tarball is headless and omits IGES, STL, BRepFeat and OCAF. Unused bindings
are dropped by `--gc-sections`, so a normal geometry path links (the
`ferrocad_occt_wasm` smoke crate builds a box, fillets an edge and tessellates it,
and returns 40 triangles when run under Node/WASI); calling those specific
bindings fails at link time.

## Code Formatting

### Rust Code
```
$ cargo +nightly fmt
```

### C++ Code
```
$ clang-format -i crates/opencascade-sys/include/wrapper.hxx
```

## Comparison to other tools

### OpenCascade C++ API

This is probably an obvious one, but I use Rust in order to avoid using C++ when possible. You can use OpenCascade directly in its native language, C++, and some people do! I don't have the patience or mental fortitude for it, though. This method of course gives you the full power of OpenCascade without having to write bindings or higher-level wrappers for it.

### [OpenSCAD](https://openscad.org/)

OpenSCAD is how I started with code-based CAD, and it's still a nice tool with lots of community projects and libraries invested into it. To me though, there are several downsides:

* The language is clumsy and limited compared to modern programming languages
* The CAD kernel is CGAL, which is mesh-based. There is less semantic information about geometry, and parts end up just being a soup of triangles.
* Fillets, chamfers, and curves in general end up being more of a pain compared to a B-Rep (Boundary Representation) CAD kernel
* No ability to export STEP files


### [CadQuery](https://cadquery.readthedocs.io/en/latest/)

This project is extremely similar to CadQuery, and owes a lot of its inspiration to it. I mostly like CadQuery, except:

* It's a Python tool, and managing Python dependencies and installations just isn't fun
* The usage of the "fluent" API produces code that is hard to visualize, you have to keep a lot on your mental stack to understand what a given snippet is doing.

These are small complaints, and to the second point, I'm pretty sure you can write more imperative CadQuery code which spells out more obviously what is going on.

I'd say CadQuery is an _excellent_ tool, and likely the most fully-featured code-based CAD tool out there that I'm aware of.

So if you like Python and have patience to deal with Python installations and such, absolutely go with CadQuery. It'll take this project quite awhile to reach feature parity with it.

### [Build123d](https://github.com/gumyr/build123d)

Build123d seems to be an evolution of CadQuery. Still in Python, it replaces the "fluent" API with stateful context managers using `with` blocks. It's still an early project and I haven't looked closely at it, but I do wonder if the context-manager approach will lead to lots of rightward drift in code. Aside from that, it seems like a reasonable syntax approach for CAD modeling.

Still has the same downsides of managing a Python installation and managing how you distribute that.

### [Cascade Studio](https://github.com/zalo/CascadeStudio)

Like CadQuery, Cascade Studio is also based on the OpenCascade kernel. It's quite nice as well, and has an [incredible manual](https://github.com/raydeleu/CascadeStudioManual) with tons of detail. I was mainly turned off by the fact that you have to use the GUI to discover edge indices, which you then pass to the `FilletEdges()` function as a list of numbers. These indices can change as you modify the shape, and it all feels a bit unstable and relies too much on mouse picking from the GUI.

But its web browser support and relatively simple JavaScript API make it a nice, approachable tool if you want to create models quickly.

### [DeclaraCAD](https://declaracad.com/docs/introduction/)

Also based on OpenCascade, DeclaraCAD aims to allow you to write a declarative tree which represents all the operations you perform to create a shape. It seems to have quite rich support for sketches, part modeling, and part assembly. It is distributed as a Qt application and is fully offline and driven by user text files - nice! I would personally worry about the rightward drift of code for non-trivial models, and my brain doesn't really think in a tree the way the code is structured, but if you're a LISPer this is probably perfect!

### [Fornjot](https://github.com/hannobraun/fornjot)

Fornjot is an early-stage B-Rep kernel, written in Rust. I think the project has a lot of potential, but of course being an early-stage project, it's not nearly as featureful as something like OpenCascade, which has had decades of development behind it.

At the same time, I think Rust gives you the power to take on large ambitious projects and keep things organized, so if the maintainer can keep momentum and build a community of contributors behind the project, we may have a nice, pure-Rust solution to code-based CAD.

For now though, I'd rather build a nice Rust API on top of OpenCascade, and then perhaps add Fornjot as a backend to that API when the project is farther along.
