#pragma once

#include <IGUI/IRenderWindow.h>

#include <QWidget>

class QMouseEvent;

namespace GUIQt {
class CRenderWindow
  : public QWidget
  , public IGUI::IRenderWindow
{
  Q_OBJECT

public:
  explicit CRenderWindow(QWidget* = nullptr);

  void* nativeWindow() const override;

  MathTypes::UIntSize2D size() const override;

  void trackMousePress(const SlotForMouseSignal&) const override;
  void trackMouseRelease(const SlotForMouseSignal&) const override;
  void trackMouseMove(const SlotForMouseSignal&) const override;

protected:
  void mousePressEvent(QMouseEvent* event) override;
  void mouseReleaseEvent(QMouseEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;

  QPaintEngine* paintEngine() const override;

private:
  mutable MouseSignal m_mousePressedSignal;
  mutable MouseSignal m_mouseReleasedSignal;
  mutable MouseSignal m_mouseMovedSignal;
};
}