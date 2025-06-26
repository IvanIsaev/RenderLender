#include "CObjectLoader.h"

#include "CMaterialManager.h"
#include "CSceneLoader.h"
#include "Conversation.h"

#include <filament/IndexBuffer.h>
#include <filament/RenderableManager.h>
#include <filament/Scene.h>
#include <filament/TransformManager.h>
#include <filament/VertexBuffer.h>

#include <utils/Entity.h>
#include <utils/EntityManager.h>

#include <math/vec3.h>

using namespace RendererFilament;

namespace {
enum BufferIndexes
{
  kGeometryBufferIndex,
  kColorBufferIndex,
  kTBNBufferIndex
};
}

RendererFilament::CObjectLoader::CObjectLoader(
  EngineShared pEngine,
  filament::Scene& scene,
  CMaterialManager& materialManager)
  : m_pVertexBufferManager(std::make_shared<CVertexBufferManager>())
  , m_pIndexBufferManager(std::make_shared<CIndexBufferManager>())
  , m_pEngine(pEngine)
  , m_scene(scene)
  , m_materialManager(materialManager)
{
}

void
CObjectLoader::load(const Scene::Scene& scene)
{
  auto loadToFilament = [this](const auto& object) { return load(object); };

  auto loadScene = CSceneLoader{ m_materialManager };
  loadScene(scene, loadToFilament);
}

VertexBufferUnique
CObjectLoader::createVertexBuffer(EngineShared pEngine,
                                  const Vertices& vertices)
{
  using namespace filament;

  const auto pVertexBuffer =
    VertexBuffer::Builder()
      .vertexCount(static_cast<uint32_t>(vertices.coords.size()))
      .bufferCount(3)
      .attribute(VertexAttribute::POSITION,
                 kGeometryBufferIndex,
                 VertexBuffer::AttributeType::FLOAT3,
                 0,
                 sizeOfCoord)
      .attribute(VertexAttribute::TANGENTS,
                 kTBNBufferIndex,
                 VertexBuffer::AttributeType::SHORT4,
                 0,
                 sizeOfTBN)
      .normalized(VertexAttribute::TANGENTS)
      .attribute(VertexAttribute::COLOR,
                 kColorBufferIndex,
                 VertexBuffer::AttributeType::UBYTE4,
                 0,
                 sizeOfColor)
      .normalized(VertexAttribute::COLOR)
      .build(*pEngine);

  return VertexBufferUnique(pVertexBuffer, FilamentComponentCleaner(pEngine));
}

IndexBufferUnique
CObjectLoader::createIndexBuffer(EngineShared pEngine, const Faces& faces)
{
  using namespace filament;

  const auto pIndexBuffer =
    IndexBuffer::Builder()
      .indexCount(static_cast<uint32_t>(faces.size()) * 3)
      .bufferType(IndexBuffer::IndexType::UINT)
      .build(*pEngine);
  return IndexBufferUnique(pIndexBuffer, FilamentComponentCleaner(pEngine));
}

EntityUnique
CObjectLoader::createRenderable(EngineShared pEngine,
                                filament::VertexBuffer* pVertexBuffer,
                                filament::IndexBuffer* pIndexBuffer,
                                const Faces& faces,
                                uint32_t materialIndex)
{
  using namespace filament;

  const auto pMaterialInstance =
    m_materialManager.getMaterialInstance(materialIndex);
  const auto renderable = utils::EntityManager::get().create();
  const auto result = RenderableManager::Builder(1)
                        .boundingBox({ { -1, -1, -1 }, { 1, 1, 1 } })
                        .material(0, pMaterialInstance)
                        .geometry(0,
                                  RenderableManager::PrimitiveType::TRIANGLES,
                                  pVertexBuffer,
                                  pIndexBuffer,
                                  0,
                                  faces.size() * 3)
                        .culling(false)
                        .receiveShadows(true)
                        .castShadows(true)
                        .build(*pEngine, renderable);

  return EntityUnique(new CEntity(renderable),
                      FilamentComponentCleaner(pEngine));
}

uint32_t
CObjectLoader::load(const Object& object)
{
  using namespace filament;

  const auto pObject =
    m_objectsForDelete.emplace_back(std::make_unique<Object>(object)).get();

  const auto coordSize =
    sizeOfCoord * pObject->meshes[0].vertices.coords.size();
  const auto colorSize =
    sizeOfColor * pObject->meshes[0].vertices.colors.size();
  const auto TBNSize = sizeOfTBN + pObject->meshes[0].vertices.tbn.size();

  auto pVertexBuffer =
    createVertexBuffer(m_pEngine, pObject->meshes[0].vertices);
  pVertexBuffer->setBufferAt(
    *m_pEngine,
    kGeometryBufferIndex,
    VertexBuffer::BufferDescriptor(
      pObject->meshes[0].vertices.coords.data(),
      coordSize,
      nullptr)); // TODO: realize callback to release memory
  pVertexBuffer->setBufferAt(
    *m_pEngine,
    kColorBufferIndex,
    VertexBuffer::BufferDescriptor(
      pObject->meshes[0].vertices.colors.data(),
      colorSize,
      nullptr)); // TODO: realize callback to release memory
  pVertexBuffer->setBufferAt(
    *m_pEngine,
    kTBNBufferIndex,
    VertexBuffer::BufferDescriptor(
      pObject->meshes[0].vertices.tbn.data(), TBNSize, nullptr));

  const auto indecesSize = sizeOfFace * pObject->meshes[0].faces.size();
  auto pIndexBuffer = createIndexBuffer(m_pEngine, pObject->meshes[0].faces);
  pIndexBuffer->setBuffer(
    *m_pEngine,
    IndexBuffer::BufferDescriptor(
      pObject->meshes[0].faces.data(),
      indecesSize,
      nullptr)); // TODO: realize callback to release memory

  auto pRenderable = createRenderable(m_pEngine,
                                      pVertexBuffer.get(),
                                      pIndexBuffer.get(),
                                      pObject->meshes[0].faces,
                                      pObject->meshes[0].materialIndex);

  auto& transformManager = m_pEngine->getTransformManager();

  auto importedObjectTransformInstance =
    transformManager.getInstance(pRenderable->entityId());

  const auto transformMatrix =
    convertToFilamentMat(pObject->transformation) *
    transformManager.getWorldTransform(importedObjectTransformInstance);
  m_scene.addEntity(pRenderable->entityId());

  if (pObject->parent_id.has_value()) {
    const auto parentId = pObject->parent_id.value();

    auto parentInstance =
      transformManager.getInstance(utils::Entity::import(parentId));
    transformManager.setParent(importedObjectTransformInstance, parentInstance);
  }

  transformManager.openLocalTransformTransaction();
  transformManager.setTransform(importedObjectTransformInstance,
                                transformMatrix);
  transformManager.commitLocalTransformTransaction();

  m_pVertexBufferManager->addBuffer(std::move(pVertexBuffer));
  m_pIndexBufferManager->addBuffer(std::move(pIndexBuffer));

  const auto entityOfLoadedObject = pRenderable->entityId().getId();
  m_renderables.push_back(std::move(pRenderable));

  return entityOfLoadedObject;
}