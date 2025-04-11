#include "CFilamentRendererFacade.h"

CFilamentRendererFacade::CFilamentRendererFacade()
  : m_pFilamentRenderer(std::make_unique<CFilamentRenderer>())
  , m_pMouseCursorHandler(nullptr)
{
}

void
CFilamentRendererFacade::init(const RenderConfig& settings)
{
  m_pFilamentRenderer->init(settings);

  auto& cameraOperator = m_pFilamentRenderer->cameraOperator();
  m_pMouseCursorHandler =
    std::make_unique<CMouseCursorHandler>(this, cameraOperator);
}

IMouseCursorHandler*
CFilamentRendererFacade::mouseCursorHandler()
{
  return m_pMouseCursorHandler.get();
}

void
CFilamentRendererFacade::execute()
{
  m_pFilamentRenderer->execute();
}
