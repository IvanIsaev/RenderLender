#pragma once

class IRenderWindow
{
public:
  virtual ~IRenderWindow() = default;

  virtual void* nativeWindow() const = 0;
};