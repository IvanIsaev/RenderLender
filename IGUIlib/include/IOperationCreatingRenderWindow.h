#pragma once

#include <string_view>

class IRenderWindow;

class IOperationCreatingRenderWindow
{
public:
  virtual ~IOperationCreatingRenderWindow() = default;

  virtual void addRenderWindow(std::string_view) = 0;
  virtual IRenderWindow* lastAddedRenderWindow() = 0;
};
