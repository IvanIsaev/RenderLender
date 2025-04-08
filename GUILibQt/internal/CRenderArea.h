#pragma once

#include <IRenderArea.h>

#include <QtWidgets/QTabWidget>

class CRenderArea
  : public QTabWidget
  , public IRenderArea
{
  Q_OBJECT

public:
  std::unique_ptr<IOperationCreatingRenderWindow>
  operationForCreatingRenderWindow() override;
};