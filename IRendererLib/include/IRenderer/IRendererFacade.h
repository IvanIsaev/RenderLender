#pragma once

namespace IRenderer {
class IMouseCursorHandler;
class IObjectLoader;

struct RenderConfig;
}

namespace IRenderer {
class IRendererFacade
{
public:
  virtual ~IRendererFacade() = default;

  virtual void init(const RenderConfig&) = 0;

  virtual IMouseCursorHandler& mouseCursorHandler() = 0;

  virtual IObjectLoader& objectLoader() = 0;

  virtual void execute() = 0;
};
}