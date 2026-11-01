#pragma once

// One translation unit for the Part-layer bridge: the order matters, `geom2d`
// and `part_ops` call helpers the earlier headers define.

#include "ferrocad_part_cxx/include/curve.hxx"
#include "ferrocad_part_cxx/include/geom2d.hxx"
