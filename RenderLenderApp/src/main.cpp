#include <GUIQt/CApplicationFactory.h>
#include <GUIQt/CInterfaceFactory.h>

#include <RendererFilament/CFilamentRendererFactory.h>

#include <Sceneimporter/CSceneImporterFactory.h>

#include <IGUI/IOperationCreatingRenderWindow.h>
#include <IGUI/IRenderArea.h>
#include <IGUI/IRenderWindow.h>

#include <IRenderer/IMaterialManager.h>
#include <IRenderer/IMouseCursorHandler.h>
#include <IRenderer/IObjectLoader.h>
#include <IRenderer/Object.h>
#include <IRenderer/RenderConfig.h>

#include <RLMath/Matrix.h>

#include <Scene/Scene.h>

#include <functional>

namespace {
void
loadNode(const Scene::Node& node,
         const std::vector<Scene::Mesh>& meshes,
         IRenderer::IObjectLoader& objectLoader,
         IRenderer::IMaterialManager& materialManager,
         std::optional<uint32_t> parentId = std::nullopt)
{
  auto idOfParent = std::optional<uint32_t>{};

  if (node.meshesIds.size()) {
    const auto& meshIds = node.meshesIds;

    auto object = IRenderer::Object{};
    object.meshes.reserve(meshIds.size());
    for (const auto meshId : meshIds) {

      const auto& mesh = meshes.at(meshId);
      auto& filamentMesh = object.meshes.emplace_back();

      for (const auto& face : mesh.faces) {
        assert(face.verticesId.size() == 3);

        filamentMesh.faces.push_back({ face.verticesId.at(0),
                                       face.verticesId.at(1),
                                       face.verticesId.at(2) });
      }

      for (const auto& vertex : mesh.vertices) {
        filamentMesh.vertices.coords.emplace_back(vertex);
        filamentMesh.vertices.colors.emplace_back(0x000000ff);
      }

      filamentMesh.materialIndex = materialManager.defaultMaterialInstanceId();
    }

    object.transformation = RLMath::transposedCopy(node.transformation);
    object.parent_id = parentId;

    objectLoader.loadObject(object);
    idOfParent = objectLoader.idLastLoadedObject();
  }

  for (const auto pChild : node.children) {
    loadNode(*pChild, meshes, objectLoader, materialManager, idOfParent);
  }
}

void
loadScene(const Scene::Scene& scene, IRenderer::IRendererFacade& rendererFacade)
{
  const auto pRoot = scene.root;
  loadNode(*pRoot, scene.meshes, rendererFacade.objectLoader(), rendererFacade.materialManager());
}
}

int
main(int argc, char* argv[])
{
  auto sceneImporterFactory =
    CSceneImporterFactory{ "e:\\tmp\\cube1\\file.gltf" };
  const auto pSceneImporter = sceneImporterFactory.create();
  const auto pScene = pSceneImporter->import();

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

  loadScene(*pScene.get(), *pRenderer.get());

  pRenderer->execute();

  return pApplication->execute();
}
