#pragma once

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xyz.hpp>
#include <boost/qvm.hpp>

using FloatMatrix4x4 = boost::qvm::mat<float, 4, 4>;
using FloatPointXYZ = boost::geometry::model::d3::point_xyz<float>;