#include "CApplication.h"

using namespace GUIQt;

CApplication::CApplication(int argc, char* argv[])
  : QApplication(argc, argv)
{
}

bool
CApplication::execute()
{
  return QApplication::exec();
}
