#pragma once

#include <Bnd_Box.hxx>
#include <Precision.hxx>

// Bounding-box measurements and OCCT's default tolerance: the two calls that
// `opencascade-sys` does not expose beyond `Bnd_Box` construction and corners.

// The squared diagonal of the box (`Bnd_Box::SquareExtent`).
inline double fc_bnd_box_square_extent(const Bnd_Box& bnd_box)
{
    return bnd_box.SquareExtent();
}

// OCCT's default linear tolerance (`Precision::Confusion`, 1e-7).
inline double fc_precision_confusion()
{
    return Precision::Confusion();
}
