#pragma once

#include <Size2D.h>

#include <IMouseCursorHandler.h>

class CMouseCursorHandler : public IMouseCursorHandler
{
public:
  virtual ~CMouseCursorHandler() = default;

  void handleMousePress(const IntVector2D&) override;
  void handleMouseRelease(const IntVector2D&) override;
  void handleMouseMove(const IntVector2D&) override;
};
