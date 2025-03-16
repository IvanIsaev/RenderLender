#pragma once

#include <Size2D.h>

class IRenderer
{
public:
  struct Config
  {
    void* nativeWindow;
    Size2D<int> windowSize;
  };

public:
  virtual ~IRenderer() = default;

  virtual void init(const Config&) = 0;

  virtual bool execute() = 0;
};
