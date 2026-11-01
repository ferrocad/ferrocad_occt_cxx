#pragma once

// Typed binding: general (affine) shape transform.
//
// `BRepBuilderAPI_Transform` takes a `gp_Trsf`, which is a similarity and
// cannot express a non-uniform scale or shear. `BRepBuilderAPI_GTransform`
// takes a `gp_GTrsf` and accepts any affine 3x4 matrix.
//
// The matrix is row-major 4x4, matching the Rust caller's `Matrix4`; OCCT's
// `gp_GTrsf::SetValue` is 1-based `(row, column)`.
//
// OCCT 7.x's `Standard_Failure` does not derive from `std::exception`, so it
// must be caught here and translated to a `std::exception` for cxx's `Result`
// shim. No OCCT exception may cross the bridge.

#include <BRepBuilderAPI_GTransform.hxx>
#include <Standard_Failure.hxx>
#include <TopoDS_Shape.hxx>
#include <gp_GTrsf.hxx>

#include <memory>
#include <stdexcept>

#include "rust/cxx.h"

inline std::unique_ptr<TopoDS_Shape> gtransform(const TopoDS_Shape& shape,
                                                rust::Slice<const double> matrix)
{
    if (shape.IsNull())
        throw std::invalid_argument("gtransform: null shape");
    if (matrix.size() != 16)
        throw std::invalid_argument("gtransform: expected a row-major 4x4 matrix");

    try
    {
        gp_GTrsf trsf;
        for (int row = 1; row <= 3; ++row)
            for (int column = 1; column <= 4; ++column)
                trsf.SetValue(row, column, matrix[(row - 1) * 4 + (column - 1)]);

        BRepBuilderAPI_GTransform op(shape, trsf, Standard_True);
        if (!op.IsDone())
            throw std::runtime_error("BRepBuilderAPI_GTransform did not complete");

        const TopoDS_Shape& result = op.Shape();
        if (result.IsNull())
            throw std::runtime_error("BRepBuilderAPI_GTransform produced no shape");

        return std::make_unique<TopoDS_Shape>(result);
    }
    catch (const Standard_Failure& failure)
    {
        const char* message = failure.GetMessageString();
        throw std::runtime_error(message && *message ? message : "OCCT reported a failure");
    }
    catch (const std::exception&)
    {
        // Our own failures above; cxx's `Result` shim turns them into `Err`.
        throw;
    }
    catch (...)
    {
        throw std::runtime_error("unknown OCCT exception");
    }
}
