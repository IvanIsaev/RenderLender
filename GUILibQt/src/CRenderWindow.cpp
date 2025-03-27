#include <CRenderWindow.h>

#include <QResizeEvent>
#include <QSize>

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

Size2D<int>
CRenderWindow::size() const
{
  const auto dpr = QWidget::devicePixelRatio();
  const auto widgetSize = QWidget::size() * dpr;
  return Size2D<int>{ .width = widgetSize.width(),
                      .height = widgetSize.height() };
}

void
CRenderWindow::resizeEvent(QResizeEvent* event)
{
  // TODO: Realize resize event for renderer [isaev]
  QWidget::resizeEvent(event);
}

QPaintEngine*
CRenderWindow::paintEngine() const
{
  return nullptr;
}