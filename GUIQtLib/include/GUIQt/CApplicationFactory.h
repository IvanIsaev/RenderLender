#pragma once

#include "guilib_export.h"

#include <IGUI/IApplication.h>

#include <memory>

class GUILIB_EXPORT CApplicationFactory
{
public:
  static std::unique_ptr<IApplication> create(int, char*[]);
};
