#pragma once

#include <string_view>

namespace IGUI {
class IRenderWindow;
}

namespace IGUI {
class IOperationCreatingRenderWindow
{
public:
  virtual ~IOperationCreatingRenderWindow() = default;

  virtual void addRenderWindow(std::string_view) = 0;
  virtual IRenderWindow* lastAddedRenderWindow() = 0;
};
}