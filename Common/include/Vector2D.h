#pragma once

#include <concepts>

template<typename T>
concept SizeType = std::unsigned_integral<T> || std::floating_point<T>;

template<typename SizeType>
struct Vector2D
{
  SizeType width = 0;
  SizeType height = 0;
};

using IntVector2D = Vector2D<int>;