#include "CFilamentRendererFacade.h"

using namespace RendererFilament;

CFilamentRendererFacade::CFilamentRendererFacade()
  : m_pFilamentRenderer(std::make_unique<CFilamentRenderer>())
  , m_pMouseCursorHandler(nullptr)
{
}

void
CFilamentRendererFacade::init(const IRenderer::RenderConfig& settings)
{
  m_pFilamentRenderer->init(settings);

  auto& cameraOperator = m_pFilamentRenderer->cameraOperator();
  m_pMouseCursorHandler =
    std::make_unique<CMouseCursorHandler>(this, cameraOperator);

  m_pMaterialManager =
    std::make_unique<CMaterialManager>(m_pFilamentRenderer->engine());
  m_pMaterialManager->init();

  m_pObjectLoader = std::make_unique<CObjectLoader>(m_pFilamentRenderer->engine(),
                                    m_pFilamentRenderer->scene(),
                                    *m_pMaterialManager);

  m_pLightManager = std::make_unique<CLightManager>(
    m_pFilamentRenderer->engine(), m_pFilamentRenderer->scene());
}

IRenderer::IMouseCursorHandler&
CFilamentRendererFacade::mouseCursorHandler()
{
  return *m_pMouseCursorHandler;
}

IRenderer::IObjectLoader&
CFilamentRendererFacade::objectLoader()
{
  return *m_pObjectLoader;
}

IRenderer::IMaterialManager&
CFilamentRendererFacade::materialManager()
{
  return *m_pMaterialManager;
}

void
CFilamentRendererFacade::execute()
{
  m_pFilamentRenderer->execute();
}
