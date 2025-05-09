#include <GUIQt/CApplicationFactory.h>
#include <GUIQt/CInterfaceFactory.h>

#include <RendererFilament/CFilamentRendererFactory.h>

#include <Sceneimporter/CSceneImporterFactory.h>

#include <IGUI/IOperationCreatingRenderWindow.h>
#include <IGUI/IRenderArea.h>
#include <IGUI/IRenderWindow.h>

#include <IRenderer/RenderConfig.h>

#include <Scene/Scene.h>

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
  const auto config =
    RenderConfig{ .nativeWindow = nativeWindow, .windowSize = windowSize };

  auto pRenderer = CFilamentRendererFactory::create();
  pRenderer->init(config);

  auto pMouseCursorHandler = pRenderer->mouseCursorHandler();
  pLastWindow->trackMousePress(std::bind(&IMouseCursorHandler::handleMousePress,
                                         pMouseCursorHandler,
                                         std::placeholders::_1));
  pLastWindow->trackMouseRelease(
    std::bind(&IMouseCursorHandler::handleMouseRelease,
              pMouseCursorHandler,
              std::placeholders::_1));
  pLastWindow->trackMouseMove(std::bind(&IMouseCursorHandler::handleMouseMove,
                                        pMouseCursorHandler,
                                        std::placeholders::_1));

  pRenderer->execute();

  return pApplication->execute();
}
