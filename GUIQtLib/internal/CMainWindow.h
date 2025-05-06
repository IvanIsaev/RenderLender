#pragma once

#include "CRenderArea.h"

#include <IGUI/IInterface.h>

#include <ui_CMainWindow.h>

#include <QtWidgets/QMainWindow>

class CMainWindow
  : public QMainWindow
  , public IInterface
{
  Q_OBJECT

public:
  explicit CMainWindow(QWidget* parent = nullptr);
  ~CMainWindow() = default;

  // Inherited via IInterface
  void init() override;
  void show() override;

  IRenderArea* renderArea() override;

private:
  Ui::CMainWindowClass ui;

  CRenderArea* m_renderArea;
};
