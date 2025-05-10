#pragma once

#include <IGUI/IApplication.h>

#include <QtWidgets/QApplication>

namespace GUIQt {
class CApplication
  : public QApplication
  , public IGUI::IApplication
{
  Q_OBJECT

public:
  explicit CApplication(int, char*[]);
  ~CApplication() = default;

  // Inherited via IApplication
  bool execute() override;
};
}
