#include "CRenderArea.h"
#include "COperationCreatingRenderWindow.h"
#include "CRenderWindow.h"

using namespace GUIQt;

std::unique_ptr<IGUI::IOperationCreatingRenderWindow>
CRenderArea::operationForCreatingRenderWindow()
{
  return std::make_unique<COperationCreatingRenderWindow>(*this);
}
