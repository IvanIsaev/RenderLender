#include <CRenderWindow.h>

#include <QResizeEvent>
#include <QSize>

CRenderWindow::CRenderWindow(IEventWindow& eventWindow)
  : m_eventWindow{ eventWindow }
{
}

void*
CRenderWindow::nativeWindow() const
{
  return reinterpret_cast<void*>(QWidget::winId());
}

void
CRenderWindow::resizeEvent(QResizeEvent* event)
{
  const auto& qSize = event->size();
  const auto newSize = Size{ .width = qSize.width(), .height = qSize.height() };

  m_eventWindow.resize(newSize);

  QWidget::resizeEvent(event);
}
