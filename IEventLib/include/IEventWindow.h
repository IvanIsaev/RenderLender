#pragma once

struct Size
{
  int width = 0;
  int height = 0;
};

class IEventWindow
{
public:
  virtual ~IEventWindow() = default;

  virtual void resize(const Size&) = 0;
};
