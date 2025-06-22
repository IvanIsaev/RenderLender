#pragma once

#include <cstddef>
#include <cstdint>

namespace RendererFilament {
struct Color
{
  Color(uint32_t color)
  {
    r = static_cast<std::byte>((color >> 24) & 0xff);
    g = static_cast<std::byte>((color >> 16) & 0xff);
    b = static_cast<std::byte>((color >> 8) & 0xff);
    a = static_cast<std::byte>((color) & 0xff);
  }

  std::byte r;
  std::byte g;
  std::byte b;
  std::byte a;
};

static constexpr auto sizeOfColor = sizeof(Color);
}