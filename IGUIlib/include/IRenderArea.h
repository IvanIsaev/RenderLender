#pragma once

#include <memory>
#include <string_view>

class IOperationCreatingRenderWindow;

class IRenderArea
{
public:
  virtual ~IRenderArea() = default;

  virtual std::unique_ptr<IOperationCreatingRenderWindow>
  operationForCreatingRenderWindow() = 0;
};