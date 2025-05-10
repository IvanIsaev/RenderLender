#pragma once

#include <MathTypes/Point.h>

namespace IRenderer {
class IMouseCursorHandler
{
public:
  virtual ~IMouseCursorHandler() = default;

  virtual void handleMousePress(const MathTypes::UIntPoint2D&) = 0;
  virtual void handleMouseRelease(const MathTypes::UIntPoint2D&) = 0;
  virtual void handleMouseMove(const MathTypes::UIntPoint2D&) = 0;
};
}