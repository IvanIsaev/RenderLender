#include "CMainWindow.h"

#include <QHBoxLayout>

CMainWindow::CMainWindow(QWidget* parent)
  : QMainWindow(parent)
  , m_renderArea(nullptr)
{
  ui.setupUi(this);
}

void
CMainWindow::init()
{
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

IRenderArea*
CMainWindow::renderArea()
{
  return m_renderArea;
}
