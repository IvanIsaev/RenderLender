#pragma once

#include <concepts>

template<typename T>
concept SizeType = std::unsigned_integral<T> || std::floating_point<T>;

template<SizeType T>
struct Point2D
{
  T x = 0;
  T y = 0;
};
using IntPoint2D = Point2D<uint32_t>;

template<SizeType T>
struct Size2D
{
  T width = 0;
  T height = 0;
};
using IntSize2D = Size2D<uint32_t>;