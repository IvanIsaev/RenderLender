#include "GUIQt/CInterfaceFactory.h"
#include "CMainWindow.h"

using namespace GUIQt;

std::unique_ptr<IGUI::IInterface>
CInterfaceFactory::create()
{
  return std::make_unique<CMainWindow>();
}
