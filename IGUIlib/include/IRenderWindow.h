#pragma once

#include <Size2D.h>

class IRenderWindow
{
public:
  virtual ~IRenderWindow() = default;

  virtual void* nativeWindow() const = 0;

  virtual Size2D<int> size() const = 0;
};