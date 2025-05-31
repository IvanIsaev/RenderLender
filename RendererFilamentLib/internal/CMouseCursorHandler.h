#pragma once

#include <MathTypes/Point.h>

#include <IRenderer/IMouseCursorHandler.h>

namespace IRenderer {
class IRendererFacade;
}

namespace RendererFilament {
class COperator;
}

namespace RendererFilament {
class CMouseCursorHandler : public IRenderer::IMouseCursorHandler
{
public:
  explicit CMouseCursorHandler(IRenderer::IRendererFacade*, COperator&);
  virtual ~CMouseCursorHandler() = default;

  void handleMousePress(const MathTypes::UIntPoint2D&,
                        Miscellaneous::MouseButtonType) override;
  void handleMouseRelease(const MathTypes::UIntPoint2D&,
                          Miscellaneous::MouseButtonType) override;
  void handleMouseMove(const MathTypes::UIntPoint2D&,
                       Miscellaneous::MouseButtonType) override;

private:
  IRenderer::IRendererFacade* m_pRenderer;
  COperator& m_cameraOperator;
};
}