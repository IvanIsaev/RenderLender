#include "CMouseCursorHandler.h"
#include "COperator.h"

#include <IRenderer/IRendererFacade.h>

#include <camutils/Manipulator.h>
#include <filament/Camera.h>

#include <iostream>

using namespace RendererFilament;

CMouseCursorHandler::CMouseCursorHandler(IRenderer::IRendererFacade* pRenderer,
                                         COperator& cameraOperator)
  : m_pRenderer(pRenderer)
  , m_cameraOperator(cameraOperator)
{
}

void
CMouseCursorHandler::handleMousePress(const MathTypes::UIntPoint2D& position)
{
  if (m_pRenderer) {
    m_cameraOperator.grabBegin(position.x(), position.y(), false);
    m_pRenderer->execute();
  }
}

void
CMouseCursorHandler::handleMouseRelease(const MathTypes::UIntPoint2D& position)
{
  if (m_pRenderer) {
    m_cameraOperator.grabEnd();
    m_pRenderer->execute();
  }
}

void
CMouseCursorHandler::handleMouseMove(const MathTypes::UIntPoint2D& position)
{
  if (m_pRenderer) {
    m_cameraOperator.grabUpdate(position.x(), position.y());
    m_pRenderer->execute();
  }
}
