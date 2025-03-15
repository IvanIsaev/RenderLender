#pragma once

#include <QtWidgets/QMainWindow>

#include <ui_CMainWindow.h>

#include <IInterface.h>

class CMainWindow : public QMainWindow, public IInterface
{
    Q_OBJECT

public:
    explicit CMainWindow(QWidget *parent = nullptr);
    ~CMainWindow() = default;

    // Inherited via IInterface
    void show ( ) override;

private:
    Ui::CMainWindowClass ui;
};
