#include "CMainWindow.h"


CMainWindow::CMainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

void CMainWindow::show ( )
{
    QMainWindow::show ( );
}
