#include "CMainWindow.h"


CMainWindow::CMainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

CMainWindow::~CMainWindow()
{}

void CMainWindow::show ( )
{
    QMainWindow::show ( );
}
