#include "COperationCreatingRenderWindow.h"
#include "CRenderWindow.h"

#include <QTabWidget>

using namespace GUIQt;

COperationCreatingRenderWindow::COperationCreatingRenderWindow(
  QTabWidget& windowCollection)
  : m_windowCollection(windowCollection)
  , m_lastAddedRenderWindow(nullptr)
{
}

void
COperationCreatingRenderWindow::addRenderWindow(std::string_view title)
{
  auto pRenderWindow = new CRenderWindow;

  m_windowCollection.addTab(pRenderWindow, QString(title.data()));

  m_lastAddedRenderWindow = pRenderWindow;
}

IGUI::IRenderWindow*
COperationCreatingRenderWindow::lastAddedRenderWindow()
{
  return m_lastAddedRenderWindow;
}
