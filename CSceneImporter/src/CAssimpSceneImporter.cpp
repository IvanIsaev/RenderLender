#include "CAssimpSceneImporter.h"

#include "Utils.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include <memory>
#include <ranges>
#include <span>

namespace {
std::vector<Face>
importFaces(std::span<aiFace> aiFaces)
{
  const auto toSpan = [](const auto& aiFace) {
    return std::span<unsigned int>{ aiFace.mIndices, aiFace.mNumIndices };
  };

  const auto toFace = [](auto aiFaceSpan) {
    return Face{ .verticesId = std::vector<unsigned int>(aiFaceSpan.begin(),
                                                         aiFaceSpan.end()) };
  };

  return aiFaces | std::views::transform(toSpan) |
         std::views::transform(toFace) | std::ranges::to<std::vector<Face>>();
}

std::vector<FloatPoint3D>
importVertices(std::span<aiVector3D> aiVertices)
{
  const auto toVertex = [](const auto& aiVertex) {
    return FloatPoint3D(aiVertex.x, aiVertex.y, aiVertex.z);
  };

  return aiVertices | std::views::transform(toVertex) |
         std::ranges::to<std::vector<FloatPoint3D>>();
}

std::vector<Mesh>
importMeshes(std::span<aiMesh*> aiMeshes)
{
  const auto toMesh = [](const auto pAiMesh) {
    auto mesh = Mesh{};

    mesh.faces = importFaces({ pAiMesh->mFaces, pAiMesh->mNumFaces });
    mesh.vertices =
      importVertices({ pAiMesh->mVertices, pAiMesh->mNumVertices });

    return mesh;
  };

  return aiMeshes | std::views::transform(toMesh) |
         std::ranges::to<std::vector<Mesh>>();
}

void
importNode(const aiNode* pAssimpNode, Node& pNode, Scene& scene)
{
  pNode.meshesIds = std::vector<unsigned int>(
    pAssimpNode->mMeshes, pAssimpNode->mMeshes + pAssimpNode->mNumMeshes);

  pNode.transformation =
    SceneImporter::convertMatrix(pAssimpNode->mTransformation);

  pNode.name = pAssimpNode->mName.C_Str();

  const auto numChildren = pAssimpNode->mNumChildren;

  pNode.children.reserve(numChildren);

  for (auto childIndex = 0u; childIndex < numChildren; ++childIndex) {
    auto pChildNode = scene.nodes.emplace_back(std::make_unique<Node>()).get();
    importNode(pAssimpNode->mChildren[childIndex], *pChildNode, scene);
    pNode.children.push_back(pChildNode);
  }
}

void
importNodes(const aiScene* pAssimpScene, Scene& scene)
{
  auto pRootNode = scene.nodes.emplace_back(std::make_unique<Node>()).get();
  scene.root = pRootNode;
  importNode(pAssimpScene->mRootNode, *pRootNode, scene);
}
}

CAssimpSceneImporter::CAssimpSceneImporter(
  const std::string& absolutePathToFile)
  : m_absolutePathToFile(absolutePathToFile)
{
}

SceneUnique
CAssimpSceneImporter::import() const
{
  auto importer = Assimp::Importer{};
  auto* pAssimpScene =
    importer.ReadFile(m_absolutePathToFile,
                      aiProcess_Triangulate | aiProcess_JoinIdenticalVertices |
                        aiProcess_SortByPType);

  auto pScene = std::make_unique<Scene>();

  importNodes(pAssimpScene, *pScene.get());

  if (pAssimpScene->HasMeshes())
    pScene->meshes =
      importMeshes({ pAssimpScene->mMeshes, pAssimpScene->mNumMeshes });

  return pScene;
}