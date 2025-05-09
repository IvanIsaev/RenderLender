#pragma once

#include "IMouseCursorHandler.h"
#include "RenderConfig.h"

class IRendererFacade
{
public:
  virtual ~IRendererFacade() = default;

  virtual void init(const RenderConfig&) = 0;

  virtual IMouseCursorHandler* mouseCursorHandler() = 0;

  virtual void execute() = 0;
};
