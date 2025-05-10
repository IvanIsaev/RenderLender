#pragma once

#include <MathTypes/Size.h>

namespace IRenderer {
struct RenderConfig
{
  void* nativeWindow;
  MathTypes::UIntSize2D windowSize;
};
}