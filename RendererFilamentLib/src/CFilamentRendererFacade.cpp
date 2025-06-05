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

  m_pObjectLoader = std::make_unique<CObjectLoader>(
    m_pFilamentRenderer->engine(), m_pFilamentRenderer->scene());

  m_pLightManager = std::make_unique<CLightManager>(
    m_pFilamentRenderer->engine(), m_pFilamentRenderer->scene());
}

IRenderer::IMouseCursorHandler&
CFilamentRendererFacade::mouseCursorHandler()
{
  return *m_pMouseCursorHandler.get();
}

IRenderer::IObjectLoader&
RendererFilament::CFilamentRendererFacade::objectLoader()
{
  return *m_pObjectLoader.get();
}

void
CFilamentRendererFacade::execute()
{
  m_pFilamentRenderer->execute();
}
