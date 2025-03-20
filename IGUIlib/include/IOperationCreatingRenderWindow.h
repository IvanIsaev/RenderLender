#pragma once

#include <string_view>

class IEventWindow;
class IRenderWindow;

class IOperationCreatingRenderWindow
{
public:
  virtual ~IOperationCreatingRenderWindow() = default;

  virtual void addRenderWindow(std::string_view, IEventWindow& eventWindow) = 0;
  virtual IRenderWindow* lastAddedRenderWindow() = 0;
};
