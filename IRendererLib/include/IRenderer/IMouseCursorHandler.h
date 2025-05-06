#pragma once

#include <MathTypes/Point.h>

class IMouseCursorHandler
{
public:
  virtual ~IMouseCursorHandler() = default;

  virtual void handleMousePress(const UIntPoint2D&) = 0;
  virtual void handleMouseRelease(const UIntPoint2D&) = 0;
  virtual void handleMouseMove(const UIntPoint2D&) = 0;
};
