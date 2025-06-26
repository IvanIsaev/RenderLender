#include "CSceneLoader.h"

#include "CMaterialManager.h"
#include "Conversation.h"

#include "Scene/Object.h"

#include <RLMath/Matrix.h>

#include <Scene/Scene.h>

#include <math/mat3.h>
#include <math/norm.h>

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
  using namespace filament::math;

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

      for (auto vertexIndex = size_t{}; vertexIndex < mesh.vertices.size();
           ++vertexIndex) {
        filamentMesh.vertices.coords.emplace_back(
          mesh.vertices.at(vertexIndex));

         const auto normal =
          convertToFilamentVector(mesh.normals.at(vertexIndex));
        const auto tangent =
          convertToFilamentVector(mesh.tangents.at(vertexIndex));
         const auto bitangent =
           convertToFilamentVector(mesh.bitangents.at(vertexIndex));

        const auto tbn = filament::math::packSnorm16(
           mat3f::packTangentFrame(
             filament::math::mat3f{ tangent, bitangent, normal })
             .xyzw);

        filamentMesh.vertices.tbn.push_back(tbn);
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
