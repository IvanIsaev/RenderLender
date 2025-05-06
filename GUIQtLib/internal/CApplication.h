#pragma once

#include <IGUI/IApplication.h>

#include <QtWidgets/QApplication>

class CApplication
  : public QApplication
  , public IApplication
{
  Q_OBJECT

public:
  explicit CApplication(int, char*[]);
  ~CApplication() = default;

  // Inherited via IApplication
  bool execute() override;
};
