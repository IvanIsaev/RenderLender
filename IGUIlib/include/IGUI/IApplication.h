#pragma once

namespace IGUI {
class IApplication
{
public:
  virtual ~IApplication() = default;

  virtual bool execute() = 0;
};
}