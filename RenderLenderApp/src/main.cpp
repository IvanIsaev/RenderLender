#include <CApplicationFactory.h>
#include <CFilamentRendererFactory.h>
#include <CInterfaceFactory.h>

#include <IOperationCreatingRenderWindow.h>
#include <IRenderArea.h>
#include <IRenderWindow.h>

int
main(int argc, char* argv[])
{
  auto pApplication = CApplicationFactory::create(argc, argv);
  auto pInterface = CInterfaceFactory::create();
  auto pRenderer = CFilamentRendererFactory::create();

  pInterface->init();
  pInterface->show();

  auto pRenderArea = pInterface->renderArea();

  auto pOperationForWindowCreating =
    pRenderArea->operationForCreatingRenderWindow();
  pOperationForWindowCreating->addRenderWindow("Filament render", pRenderer->eventWindow());
  auto pLastWindow = pOperationForWindowCreating->lastAddedRenderWindow();
  auto id = pLastWindow->nativeWindow();

  pRenderer->execute();

  return pApplication->execute();
}
