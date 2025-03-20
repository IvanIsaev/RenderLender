#pragma once

#include <IOperationCreatingRenderWindow.h>

class IRenderWindow;
class QTabWidget;

class COperationCreatingRenderWindow : public IOperationCreatingRenderWindow
{
public:
  explicit COperationCreatingRenderWindow(QTabWidget&);

  void addRenderWindow(std::string_view, IEventWindow& eventWindow) override;
  IRenderWindow* lastAddedRenderWindow() override;

private:
  QTabWidget& m_windowCollection;
  IRenderWindow* m_lastAddedRenderWindow;
};