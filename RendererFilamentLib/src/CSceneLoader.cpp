#include "CSceneLoader.h"

#include "CMaterialManager.h"

#include "Scene/Object.h"

#include <RLMath/Matrix.h>

#include <Scene/Scene.h>

#include <optional>
#include <vector>

using namespace RendererFilament;

namespace {
void
loadRecursively(const Scene::Node& node,
                const std::vector<Scene::Mesh>& meshes,
                const CMaterialManager& materialManager,
                const std::function<uint32_t(const Object&)>& load,
                std::optional<uint32_t> parentId = std::nullopt)
{
  auto idOfParent = std::optional<uint32_t>{};

  if (node.meshesIds.size()) {
    const auto& meshIds = node.meshesIds;

    auto object = Object{};
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

    idOfParent = load(object);
  }

  for (const auto pChild : node.children) {
    loadRecursively(*pChild, meshes, materialManager, load, idOfParent);
  }
}
}

CSceneLoader::CSceneLoader(const CMaterialManager& materialManager)
  : m_materialManager(materialManager)
{
}

void
CSceneLoader::operator()(
  const Scene::Scene& scene,
  const std::function<uint32_t(const Object&)>& load) const
{
  const auto pRoot = scene.root;
  loadRecursively(*pRoot, scene.meshes, m_materialManager, load);
}
