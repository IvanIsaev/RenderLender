#pragma once

#include <Vector2D.h>

#include <IMouseCursorHandler.h>

class IRenderer;
namespace filament {
namespace camutils {
template<typename T>
class Manipulator;
}
}

class CMouseCursorHandler : public IMouseCursorHandler
{
public:
  virtual ~CMouseCursorHandler() = default;

  void handleMousePress(const IntVector2D&) override;
  void handleMouseRelease(const IntVector2D&) override;
  void handleMouseMove(const IntVector2D&) override;

  void setRenderer(IRenderer*);
  void setCameraManipulator(filament::camutils::Manipulator<float>*);

private:
  IRenderer* m_pRenderer;
  filament::camutils::Manipulator<float>* m_pCameraManipulator;
};
