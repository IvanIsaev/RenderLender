#pragma once

#include "CFilamentRenderer.h"
#include "CMouseCursorHandler.h"

#include <IRenderer/IRendererFacade.h>

#include <memory>

namespace RendererFilament {
class CFilamentRendererFacade : public IRenderer::IRendererFacade
{
public:
  CFilamentRendererFacade();
  ~CFilamentRendererFacade() = default;

  void init(const IRenderer::RenderConfig&) override;

  IRenderer::IMouseCursorHandler* mouseCursorHandler() override;

  void execute() override;

private:
  std::unique_ptr<CFilamentRenderer> m_pFilamentRenderer;
  std::unique_ptr<CMouseCursorHandler> m_pMouseCursorHandler;
};
}