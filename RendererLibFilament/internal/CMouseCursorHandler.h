#pragma once

#include <Structures.h>

#include <IMouseCursorHandler.h>

class COperator;
class IRendererFacade;

class CMouseCursorHandler : public IMouseCursorHandler
{
public:
  explicit CMouseCursorHandler(IRendererFacade*, COperator&);
  virtual ~CMouseCursorHandler() = default;

  void handleMousePress(const IntPoint2D&) override;
  void handleMouseRelease(const IntPoint2D&) override;
  void handleMouseMove(const IntPoint2D&) override;

private:
  IRendererFacade* m_pRenderer;
  COperator& m_cameraOperator;
};
