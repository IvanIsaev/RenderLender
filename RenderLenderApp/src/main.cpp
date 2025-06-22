#include <GUIQt/CApplicationFactory.h>
#include <GUIQt/CInterfaceFactory.h>

#include <RendererFilament/CFilamentRendererFactory.h>

#include <Sceneimporter/CSceneImporterFactory.h>

#include <IGUI/IOperationCreatingRenderWindow.h>
#include <IGUI/IRenderArea.h>
#include <IGUI/IRenderWindow.h>

#include <IRenderer/IMouseCursorHandler.h>
#include <IRenderer/IObjectLoader.h>
#include <IRenderer/RenderConfig.h>

#include <Scene/Scene.h>

#include <functional>

int
main(int argc, char* argv[])
{
  auto pApplication = GUIQt::CApplicationFactory::create(argc, argv);
  auto pInterface = GUIQt::CInterfaceFactory::create();

  pInterface->init();
  pInterface->show();

  auto pRenderArea = pInterface->renderArea();
  auto pLastWindow = static_cast<IGUI::IRenderWindow*>(nullptr);

  {
    auto pOperationForWindowCreating =
      pRenderArea->operationForCreatingRenderWindow();
    pOperationForWindowCreating->addRenderWindow("Filament render");
    pLastWindow = pOperationForWindowCreating->lastAddedRenderWindow();
  }

  const auto windowSize = pLastWindow->size();
  const auto nativeWindow = pLastWindow->nativeWindow();
  const auto config = IRenderer::RenderConfig{ .nativeWindow = nativeWindow,
                                               .windowSize = windowSize };

  auto pRenderer = RendererFilament::CFilamentRendererFactory::create();
  pRenderer->init(config);

  auto& mouseCursorHandler = pRenderer->mouseCursorHandler();
  pLastWindow->trackMousePress(
    std::bind(&IRenderer::IMouseCursorHandler::handleMousePress,
              &mouseCursorHandler,
              std::placeholders::_1,
              std::placeholders::_2));
  pLastWindow->trackMouseRelease(
    std::bind(&IRenderer::IMouseCursorHandler::handleMouseRelease,
              &mouseCursorHandler,
              std::placeholders::_1,
              std::placeholders::_2));
  pLastWindow->trackMouseMove(
    std::bind(&IRenderer::IMouseCursorHandler::handleMouseMove,
              &mouseCursorHandler,
              std::placeholders::_1,
              std::placeholders::_2));

  {
    auto sceneImporterFactory =
      CSceneImporterFactory{ "e:\\tmp\\cube1\\file.gltf" };
    const auto pSceneImporter = sceneImporterFactory.create();
    auto pScene = pSceneImporter->import();
    pRenderer->objectLoader().load(*pScene.get());
  }

  pRenderer->execute();
  return pApplication->execute();
}
