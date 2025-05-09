#pragma once

#include <boost/geometry/geometries/point_xyz.hpp>
#include <boost/geometry/geometries/point_xy.hpp>

using FloatPoint3D = boost::geometry::model::d3::point_xyz<float>;
using UIntPoint2D = boost::geometry::model::d2::point_xy<uint32_t>;