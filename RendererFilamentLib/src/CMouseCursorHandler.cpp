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
CMouseCursorHandler::handleMousePress(const MathTypes::UIntPoint2D& position,
                                      Miscellaneous::MouseButtonType buttonType)
{
  if (!m_pRenderer)
    return;

  const auto useStrafe = buttonType == Miscellaneous::MouseButtonType::kRightButton;
  m_cameraOperator.grabBegin(position.x(), position.y(), useStrafe);
  m_pRenderer->execute();
}

void
CMouseCursorHandler::handleMouseRelease(const MathTypes::UIntPoint2D& position,
                                        Miscellaneous::MouseButtonType)
{
  if (!m_pRenderer)
    return;

  m_cameraOperator.grabEnd();
  m_pRenderer->execute();
}

void
CMouseCursorHandler::handleMouseMove(const MathTypes::UIntPoint2D& position,
                                     Miscellaneous::MouseButtonType)
{
  if (!m_pRenderer)
    return;

  m_cameraOperator.grabUpdate(position.x(), position.y());
  m_pRenderer->execute();
}
