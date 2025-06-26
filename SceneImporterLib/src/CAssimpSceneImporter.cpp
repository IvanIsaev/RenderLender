#include "CAssimpSceneImporter.h"

#include "Utils.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include <memory>
#include <ranges>
#include <span>

namespace {
std::vector<Scene::Face>
importFaces(std::span<aiFace> aiFaces)
{
  const auto toSpan = [](const auto& aiFace) {
    return std::span<unsigned int>{ aiFace.mIndices, aiFace.mNumIndices };
  };

  const auto toFace = [](auto aiFaceSpan) {
    return Scene::Face{ .verticesId = std::vector<unsigned int>(
                          aiFaceSpan.begin(), aiFaceSpan.end()) };
  };

  return aiFaces | std::views::transform(toSpan) |
         std::views::transform(toFace) |
         std::ranges::to<std::vector<Scene::Face>>();
}

std::vector<MathTypes::FloatPoint3D>
importVectors3D(std::span<aiVector3D> aiVertices)
{
  const auto toVertex = [](const auto& aiVertex) {
    return MathTypes::FloatPoint3D(aiVertex.x, aiVertex.y, aiVertex.z);
  };

  return aiVertices | std::views::transform(toVertex) |
         std::ranges::to<std::vector<MathTypes::FloatPoint3D>>();
}

std::vector<Scene::Mesh>
importMeshes(std::span<aiMesh*> aiMeshes)
{
  const auto toMesh = [](const auto pAiMesh) {
    auto mesh = Scene::Mesh{};

    mesh.faces = importFaces({ pAiMesh->mFaces, pAiMesh->mNumFaces });
    mesh.vertices =
      importVectors3D({ pAiMesh->mVertices, pAiMesh->mNumVertices });
    mesh.normals =
      importVectors3D({ pAiMesh->mNormals, pAiMesh->mNumVertices });
    mesh.tangents =
      importVectors3D({ pAiMesh->mTangents, pAiMesh->mNumVertices });
    mesh.bitangents =
      importVectors3D({ pAiMesh->mBitangents, pAiMesh->mNumVertices });

    return mesh;
  };

  return aiMeshes | std::views::transform(toMesh) |
         std::ranges::to<std::vector<Scene::Mesh>>();
}

void
importNode(const aiNode* pAssimpNode, Scene::Node& pNode, Scene::Scene& scene)
{
  pNode.meshesIds = std::vector<unsigned int>(
    pAssimpNode->mMeshes, pAssimpNode->mMeshes + pAssimpNode->mNumMeshes);

  pNode.transformation =
    SceneImporter::convertMatrix(pAssimpNode->mTransformation);

  pNode.name = pAssimpNode->mName.C_Str();

  const auto numChildren = pAssimpNode->mNumChildren;

  pNode.children.reserve(numChildren);

  for (auto childIndex = 0u; childIndex < numChildren; ++childIndex) {
    auto pChildNode =
      scene.nodes.emplace_back(std::make_unique<Scene::Node>()).get();
    importNode(pAssimpNode->mChildren[childIndex], *pChildNode, scene);
    pNode.children.push_back(pChildNode);
  }
}

void
importNodes(const aiScene* pAssimpScene, Scene::Scene& scene)
{
  auto pRootNode =
    scene.nodes.emplace_back(std::make_unique<Scene::Node>()).get();
  scene.root = pRootNode;
  importNode(pAssimpScene->mRootNode, *pRootNode, scene);
}
}

CAssimpSceneImporter::CAssimpSceneImporter(
  const std::string& absolutePathToFile)
  : m_absolutePathToFile(absolutePathToFile)
{
}

Scene::SceneUnique
CAssimpSceneImporter::import() const
{
  auto importer = Assimp::Importer{};
  auto* pAssimpScene =
    importer.ReadFile(m_absolutePathToFile,
                      aiProcess_Triangulate | aiProcess_JoinIdenticalVertices |
                        aiProcess_SortByPType);

  auto pScene = std::make_unique<Scene::Scene>();

  importNodes(pAssimpScene, *pScene.get());

  if (pAssimpScene->HasMeshes())
    pScene->meshes =
      importMeshes({ pAssimpScene->mMeshes, pAssimpScene->mNumMeshes });

  return pScene;
}