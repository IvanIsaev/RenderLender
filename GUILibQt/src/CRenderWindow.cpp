#include <CRenderWindow.h>

#include <QMouseEvent >
#include <QPoint>
#include <QSize>

namespace {
IntVector2D
qSizeToSize2D(const QSize& size)
{
  return IntVector2D{ .width = size.width(), .height = size.height() };
}

IntVector2D
qPointToSize2D(const QPoint& point)
{
  return IntVector2D{ .width = point.x(), .height = point.y() };
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

IntVector2D
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