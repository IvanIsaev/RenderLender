#pragma once

#include <Size2D.h>

class IEventWindow
{
public:
  virtual ~IEventWindow() = default;

  virtual void resize(const Size2D<int>&) = 0;
};
