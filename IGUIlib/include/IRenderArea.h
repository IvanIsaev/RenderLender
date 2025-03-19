#pragma once

#include <string_view>

#include <memory>

class IOperationCreatingRenderWindow;

class IRenderArea
{
public:
  virtual ~IRenderArea() = default;

  virtual std::unique_ptr<IOperationCreatingRenderWindow>
  operationForCreatingRenderWindow() = 0;
};