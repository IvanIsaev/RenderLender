#include <COperationCreatingRenderWindow.h>
#include <CRenderArea.h>
#include <CRenderWindow.h>

std::unique_ptr<IOperationCreatingRenderWindow>
CRenderArea::operationForCreatingRenderWindow()
{
  return std::make_unique<COperationCreatingRenderWindow>(*this);
}
