#pragma once

#include <IGUI/IRenderArea.h>

#include <QtWidgets/QTabWidget>

namespace GUIQt {
class CRenderArea
  : public QTabWidget
  , public IGUI::IRenderArea
{
  Q_OBJECT

public:
  std::unique_ptr<IGUI::IOperationCreatingRenderWindow>
  operationForCreatingRenderWindow() override;
};
}