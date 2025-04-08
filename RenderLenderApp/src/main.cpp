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

  pInterface->init();
  pInterface->show();

  auto pRenderArea = pInterface->renderArea();
  auto pLastWindow = static_cast<IRenderWindow*>(nullptr);

  {
    auto pOperationForWindowCreating =
      pRenderArea->operationForCreatingRenderWindow();
    pOperationForWindowCreating->addRenderWindow("Filament render");
    pLastWindow = pOperationForWindowCreating->lastAddedRenderWindow();
  }

  const auto windowSize = pLastWindow->size();
  const auto nativeWindow = pLastWindow->nativeWindow();
  const auto config = IRenderer::Config{ .nativeWindow = nativeWindow, .windowSize = windowSize };

  auto pRenderer = CFilamentRendererFactory::create();
  pRenderer->init(config);
  pRenderer->execute();

  return pApplication->execute();
}
