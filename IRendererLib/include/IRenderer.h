#pragma once

#include "IMouseCursorHandler.h"

#include <Size2D.h>

class IRenderer
{
public:
  struct Config
  {
    void* nativeWindow;
    IntVector2D windowSize;
  };

public:
  virtual ~IRenderer() = default;

  virtual void init(const Config&) = 0;

  virtual IMouseCursorHandler* mouseCursorHandler() = 0;
  
  virtual bool execute() = 0;
};
