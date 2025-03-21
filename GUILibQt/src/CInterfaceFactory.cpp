#pragma once

#include "CInterfaceFactory.h"

#include "CMainWindow.h"

std::unique_ptr<IInterface>
CInterfaceFactory::create()
{
  return std::make_unique<CMainWindow>();
}
