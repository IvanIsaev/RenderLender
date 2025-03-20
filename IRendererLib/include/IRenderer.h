#pragma once

class IEventWindow;

class IRenderer
{
public:
  virtual ~IRenderer() = default;

  virtual IEventWindow& eventWindow() = 0;

  virtual bool execute() = 0;
};
