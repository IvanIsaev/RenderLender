#pragma once

#include <Vector2D.h>

class IMouseCursorHandler
{
public:
  virtual ~IMouseCursorHandler() = default;

  virtual void handleMousePress(const IntVector2D&) = 0;
  virtual void handleMouseRelease(const IntVector2D&) = 0;
  virtual void handleMouseMove(const IntVector2D&) = 0;
};
