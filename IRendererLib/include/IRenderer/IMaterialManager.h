#pragma once

#include <stdint.h>

namespace IRenderer {
class IMaterialManager
{
public:
  virtual ~IMaterialManager() = default;

  virtual uint32_t defaultMaterialInstanceId() const = 0;
};
}