#pragma once

#include "Object.h"

#include <cstdint>
#include <optional>

namespace IRenderer {
class IObjectLoader
{
public:
  virtual ~IObjectLoader() = default;

  virtual void loadObject(const Object&) = 0;
  virtual std::optional<uint32_t> idLastLoadedObject() const = 0;
};
}