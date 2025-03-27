#pragma once

#include <concepts>

template<typename T>
concept SizeType = std::unsigned_integral<T> || std::floating_point<T>;

template<typename SizeType>
struct Size2D
{
  SizeType width = 0;
  SizeType height = 0;
};
