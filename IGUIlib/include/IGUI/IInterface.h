#pragma once

class IRenderArea;

class IInterface
{
public:
  virtual ~IInterface() = default;

  virtual void init() = 0;
  virtual void show() = 0;

  virtual IRenderArea* renderArea() = 0;
};
