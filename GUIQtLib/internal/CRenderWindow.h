#pragma once

#include <IGUI/IRenderWindow.h>

#include <QWidget>

class QMouseEvent;

class CRenderWindow
  : public QWidget
  , public IRenderWindow
{
  Q_OBJECT

public:
  explicit CRenderWindow(QWidget* = nullptr);

  void* nativeWindow() const override;

  UIntSize2D size() const override;

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