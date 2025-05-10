#pragma once

#include "guilib_export.h"

#include <IGUI/IApplication.h>

#include <memory>

namespace GUIQt {
class GUILIB_EXPORT CApplicationFactory
{
public:
  static std::unique_ptr<IGUI::IApplication> create(int, char*[]);
};
}
