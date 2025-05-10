#include "GUIQt/CApplicationfactory.h"
#include "CApplication.h"

using namespace GUIQt;

std::unique_ptr<IGUI::IApplication>
CApplicationFactory::create(int argc, char* argv[])
{
  return std::make_unique<CApplication>(argc, argv);
}
