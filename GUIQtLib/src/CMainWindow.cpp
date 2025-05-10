#include "CMainWindow.h"

#include <QHBoxLayout>

using namespace GUIQt;

CMainWindow::CMainWindow(QWidget* parent)
  : QMainWindow(parent)
  , m_renderArea(nullptr)
{
  ui.setupUi(this);
}

void
CMainWindow::init()
{
  setWindowState(Qt::WindowFullScreen);

  auto pCentralWidget = centralWidget();

  auto pHorizontalCentralLayout = new QHBoxLayout;
  m_renderArea = new CRenderArea;
  pHorizontalCentralLayout->addWidget(m_renderArea);

  pCentralWidget->setLayout(pHorizontalCentralLayout);
}

void
CMainWindow::show()
{
  QMainWindow::show();
}

IGUI::IRenderArea*
CMainWindow::renderArea()
{
  return m_renderArea;
}
