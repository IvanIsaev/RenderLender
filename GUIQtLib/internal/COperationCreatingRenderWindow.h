#pragma once

#include <IGUI/IOperationCreatingRenderWindow.h>

class IRenderWindow;
class QTabWidget;

namespace GUIQt {
class COperationCreatingRenderWindow
  : public IGUI::IOperationCreatingRenderWindow
{
public:
  explicit COperationCreatingRenderWindow(QTabWidget&);

  void addRenderWindow(std::string_view) override;
  IGUI::IRenderWindow* lastAddedRenderWindow() override;

private:
  QTabWidget& m_windowCollection;
  IGUI::IRenderWindow* m_lastAddedRenderWindow;
};
}