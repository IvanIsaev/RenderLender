#pragma once

#include "guilib_export.h"

#include <IInterface.h>

#include <memory>

class GUILIB_EXPORT CInterfaceFactory
{
public:
  static std::unique_ptr<IInterface> create();
};
