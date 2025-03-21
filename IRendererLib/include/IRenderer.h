#pragma once

#include <Size2D.h>

class IEventWindow;

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

  virtual IEventWindow& eventWindow() = 0;

  virtual bool execute() = 0;
};
