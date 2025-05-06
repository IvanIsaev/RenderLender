#pragma once

#include <MathTypes/Point.h>

#include <IRenderer/IMouseCursorHandler.h>

class COperator;
class IRendererFacade;

class CMouseCursorHandler : public IMouseCursorHandler
{
public:
  explicit CMouseCursorHandler(IRendererFacade*, COperator&);
  virtual ~CMouseCursorHandler() = default;

  void handleMousePress(const UIntPoint2D&) override;
  void handleMouseRelease(const UIntPoint2D&) override;
  void handleMouseMove(const UIntPoint2D&) override;

private:
  IRendererFacade* m_pRenderer;
  COperator& m_cameraOperator;
};
