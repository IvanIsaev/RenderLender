#pragma once

#include <memory>
#include <string_view>

namespace IGUI {
class IOperationCreatingRenderWindow;
}

namespace IGUI {
class IRenderArea
{
public:
  virtual ~IRenderArea() = default;

  virtual std::unique_ptr<IOperationCreatingRenderWindow>
  operationForCreatingRenderWindow() = 0;
};
}