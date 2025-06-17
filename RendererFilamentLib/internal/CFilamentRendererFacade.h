#pragma once

#include "CFilamentRenderer.h"
#include "CLightManager.h"
#include "CMaterialManager.h"
#include "CMouseCursorHandler.h"
#include "CObjectLoader.h"

#include <IRenderer/IRendererFacade.h>

#include <memory>

namespace RendererFilament {
class CFilamentRendererFacade : public IRenderer::IRendererFacade
{
public:
  CFilamentRendererFacade();
  ~CFilamentRendererFacade() = default;

  void init(const IRenderer::RenderConfig&) override;

  IRenderer::IMouseCursorHandler& mouseCursorHandler() override;

  IRenderer::IObjectLoader& objectLoader() override;

  IRenderer::IMaterialManager& materialManager() override;

  void execute() override;

private:
  std::unique_ptr<CFilamentRenderer> m_pFilamentRenderer;
  std::unique_ptr<CMouseCursorHandler> m_pMouseCursorHandler;
  std::unique_ptr<CObjectLoader> m_pObjectLoader;
  std::unique_ptr<CLightManager> m_pLightManager;
  std::unique_ptr<CMaterialManager> m_pMaterialManager;
};
}