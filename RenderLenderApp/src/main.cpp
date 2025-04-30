#include <CApplicationFactory.h>
#include <CSceneImporterFactory.h>
#include <CFilamentRendererFactory.h>
#include <CInterfaceFactory.h>

#include <IOperationCreatingRenderWindow.h>
#include <IRenderArea.h>
#include <IRenderWindow.h>

#include <RenderConfig.h>
#include <Scene.h>

#include <functional>

int
main(int argc, char* argv[])
{
  auto sceneImporterFactory =
    CSceneImporterFactory{ "e:\\tmp\\cube\\cube.gltf" };
  const auto pSceneImporter = sceneImporterFactory.create();
  const auto pScene = pSceneImporter->import();

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
  const auto config = RenderConfig{ .nativeWindow = nativeWindow, .windowSize = windowSize };

  auto pRenderer = CFilamentRendererFactory::create();
  pRenderer->init(config);

  auto pMouseCursorHandler = pRenderer->mouseCursorHandler();
  pLastWindow->trackMousePress(std::bind(&IMouseCursorHandler::handleMousePress,
                                         pMouseCursorHandler,
                                         std::placeholders::_1));
  pLastWindow->trackMouseRelease(std::bind(&IMouseCursorHandler::handleMouseRelease,
                                         pMouseCursorHandler,
                                         std::placeholders::_1));
  pLastWindow->trackMouseMove(std::bind(&IMouseCursorHandler::handleMouseMove,
                                         pMouseCursorHandler,
                                         std::placeholders::_1));
  
  pRenderer->execute();

  return pApplication->execute();
}
