#pragma once

#include <Structures.h>

class IMouseCursorHandler
{
public:
  virtual ~IMouseCursorHandler() = default;

  virtual void handleMousePress(const IntPoint2D&) = 0;
  virtual void handleMouseRelease(const IntPoint2D&) = 0;
  virtual void handleMouseMove(const IntPoint2D&) = 0;
};
