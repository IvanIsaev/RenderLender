#include "CRenderWindow.h"

#include <QMouseEvent>
#include <QPoint>
#include <QSize>

using namespace GUIQt;

namespace {
MathTypes::UIntSize2D
qSizeToSize2D(const QSize& size)
{
  return MathTypes::UIntSize2D{ static_cast<uint32_t>(size.width()),
                     static_cast<uint32_t>(size.height()) };
}

MathTypes::UIntPoint2D
qPointToSize2D(const QPoint& point)
{
  return MathTypes::UIntPoint2D{ static_cast<uint32_t>(point.x()),
                      static_cast<uint32_t>(point.y()) };
}
}

CRenderWindow::CRenderWindow(QWidget* parent)
  : QWidget(parent)
{
  setAttribute(Qt::WA_NativeWindow);
  setAttribute(Qt::WA_PaintOnScreen);
}

void*
CRenderWindow::nativeWindow() const
{
  return reinterpret_cast<void*>(QWidget::winId());
}

MathTypes::UIntSize2D
CRenderWindow::size() const
{
  return qSizeToSize2D(QWidget::size() * QWidget::devicePixelRatio());
}

void
CRenderWindow::trackMousePress(const SlotForMouseSignal& slot) const
{
  m_mousePressedSignal.connect(slot);
}

void
CRenderWindow::trackMouseRelease(const SlotForMouseSignal& slot) const
{
  m_mouseReleasedSignal.connect(slot);
}

void
CRenderWindow::trackMouseMove(const SlotForMouseSignal& slot) const
{
  m_mouseMovedSignal.connect(slot);
}

void
CRenderWindow::mousePressEvent(QMouseEvent* event)
{
  m_mousePressedSignal(
    qPointToSize2D(event->pos() * QWidget::devicePixelRatio()));

  QWidget::mousePressEvent(event);
}

void
CRenderWindow::mouseReleaseEvent(QMouseEvent* event)
{
  m_mouseReleasedSignal(
    qPointToSize2D(event->pos() * QWidget::devicePixelRatio()));

  QWidget::mouseReleaseEvent(event);
}

void
CRenderWindow::mouseMoveEvent(QMouseEvent* event)
{
  m_mouseMovedSignal(
    qPointToSize2D(event->pos() * QWidget::devicePixelRatio()));

  QWidget::mouseMoveEvent(event);
}

QPaintEngine*
CRenderWindow::paintEngine() const
{
  return nullptr;
}