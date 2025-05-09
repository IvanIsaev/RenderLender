#include "GUIQt/CApplicationfactory.h"
#include "CApplication.h"

std::unique_ptr<IApplication>
CApplicationFactory::create(int argc, char* argv[])
{
  return std::make_unique<CApplication>(argc, argv);
}
