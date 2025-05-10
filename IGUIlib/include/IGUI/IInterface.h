#pragma once

namespace IGUI {
class IRenderArea;
}

namespace IGUI {
class IInterface
{
public:
  virtual ~IInterface() = default;

  virtual void init() = 0;
  virtual void show() = 0;

  virtual IRenderArea* renderArea() = 0;
};
}