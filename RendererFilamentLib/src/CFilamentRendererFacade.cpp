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
}

IRenderer::IMouseCursorHandler*
CFilamentRendererFacade::mouseCursorHandler()
{
  return m_pMouseCursorHandler.get();
}

void
CFilamentRendererFacade::execute()
{
  m_pFilamentRenderer->execute();
}
