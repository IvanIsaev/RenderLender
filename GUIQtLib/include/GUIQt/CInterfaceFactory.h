#pragma once

#include "guilib_export.h"

#include <IGUI/IInterface.h>

#include <memory>

namespace GUIQt {
class GUILIB_EXPORT CInterfaceFactory
{
public:
  static std::unique_ptr<IGUI::IInterface> create();
};
}
