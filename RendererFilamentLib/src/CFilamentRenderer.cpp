#include "CFilamentRenderer.h"
#include "CCamera.h"
#include "CEntity.h"
#include "COperator.h"
#include "DeleteMe.h"

#include <backend/BufferDescriptor.h>
#include <backend/DriverEnums.h>
#include <camutils/Manipulator.h>
#include <filament/Engine.h>
#include <filament/IndexBuffer.h>
#include <filament/Material.h>
#include <filament/MaterialInstance.h>
#include <filament/RenderableManager.h>
#include <filament/Renderer.h>
#include <filament/Scene.h>
#include <filament/Skybox.h>
#include <filament/SwapChain.h>
#include <filament/TransformManager.h>
#include <filament/VertexBuffer.h>
#include <filament/View.h>
#include <filament/ViewPort.h>

#include <utils/Entity.h>
#include <utils/EntityManager.h>

#include <cmath>
#include <numbers>

using namespace filament;
using namespace RendererFilament;

namespace {
struct Vertex
{
  math::float2 position;
  uint32_t color;
};

static const Vertex TRIANGLE_VERTICES[3] = {
  { { 1, 0 }, 0xffff0000u },
  { { std::cos(std::numbers::pi * 2 / 3), std::sin(std::numbers::pi * 2 / 3) },
    0xff00ff00u },
  { { std::cos(std::numbers::pi * 4 / 3), std::sin(std::numbers::pi * 4 / 3) },
    0xff0000ffu },
};

static constexpr uint16_t TRIANGLE_INDICES[3] = { 0, 1, 2 };
}

CFilamentRenderer::CFilamentRenderer()
  : m_pEngine(nullptr)
  , m_pRenderer(nullptr, FilamentComponentCleaner(nullptr))
  , m_pSwapChain(nullptr, FilamentComponentCleaner(nullptr))
  , m_pMainView(nullptr, FilamentComponentCleaner(nullptr))
  , m_pScene(nullptr, FilamentComponentCleaner(nullptr))
  , m_pSkybox(nullptr, FilamentComponentCleaner(nullptr))
  , m_pVertexBuffer(nullptr, FilamentComponentCleaner(nullptr))
  , m_pIndexBuffer(nullptr, FilamentComponentCleaner(nullptr))
  , m_pRenderable(nullptr, FilamentComponentCleaner(nullptr))
  , m_pMaterial(nullptr, FilamentComponentCleaner(nullptr))
  , m_pOperator(nullptr)
{
}

CFilamentRenderer::~CFilamentRenderer() {}

void
CFilamentRenderer::init(const IRenderer::RenderConfig& settings)
{
  m_pEngine = createEngine();
  m_pRenderer = createRenderer(m_pEngine);
  m_pSwapChain = createSwapChain(m_pEngine, settings.nativeWindow);
  m_pMainView = createView(m_pEngine);

  const auto width = settings.windowSize.x();
  const auto height = settings.windowSize.y();

  auto pCamera = createCamera(m_pEngine);
  m_pMainView->setCamera(&pCamera->camera());
  m_pMainView->setViewport({ 0, 0, width, height });

  auto pCameraManipulator = createCameraManipulator(settings.windowSize);

  m_pOperator = std::make_unique<COperator>(std::move(pCamera),
                                            std::move(pCameraManipulator));
  m_pOperator->setDefaultCameraSetting(settings.windowSize);
  m_pOperator->updateCamera();

  m_pScene = createScene(m_pEngine);

  m_pMainView->setVisibleLayers(0x4, 0x4); // Magic numbers
  m_pMainView->setScene(m_pScene.get());

  m_pSkybox = createSkybox(m_pEngine);
  m_pScene->setSkybox(m_pSkybox.get());

  m_pMainView->setPostProcessingEnabled(false);

  m_pVertexBuffer = createVertexBuffer(m_pEngine);
  m_pVertexBuffer->setBufferAt(
    *m_pEngine,
    0,
    VertexBuffer::BufferDescriptor(TRIANGLE_VERTICES, 36, nullptr));

  m_pIndexBuffer = createIndexBuffer(m_pEngine);
  m_pIndexBuffer->setBuffer(
    *m_pEngine, IndexBuffer::BufferDescriptor(TRIANGLE_INDICES, 6, nullptr));

  m_pMaterial = createMaterial(m_pEngine);

  m_pRenderable =
    createRenderable(m_pEngine, m_pVertexBuffer.get(), m_pIndexBuffer.get());

  auto& transformManager = m_pEngine->getTransformManager();
  auto ti = transformManager.getInstance(m_pRenderable->entityId());
  filament::math::mat4f transform = filament::math::mat4f{
    filament::math::mat3f(1), filament::math::float3(0, 0, -10)
  } * transformManager.getWorldTransform(ti);

  m_pScene->addEntity(m_pRenderable->entityId());
  transformManager.setTransform(ti, transform);
}

EngineShared
CFilamentRenderer::createEngine() const
{
  const auto engineConfig = Engine::Config{};
  const auto engineCleaner = [](filament::Engine* pEngine) {
    Engine::destroy(&pEngine);
  };

  return EngineShared(Engine::Builder()
                        .backend(backend::Backend::VULKAN)
                        .featureLevel(backend::FeatureLevel::FEATURE_LEVEL_3)
                        .config(&engineConfig)
                        .build(),
                      engineCleaner);
}

RendererUnique
CFilamentRenderer::createRenderer(EngineShared pEngine)
{
  return RendererUnique(pEngine->createRenderer(),
                        FilamentComponentCleaner(pEngine));
}

SwapChainUnique
CFilamentRenderer::createSwapChain(EngineShared pEngine, void* pNativeWindow)
{
  return SwapChainUnique(
    m_pEngine->createSwapChain(pNativeWindow,
                               filament::SwapChain::CONFIG_HAS_STENCIL_BUFFER),
    FilamentComponentCleaner(pEngine));
}

ViewUnique
CFilamentRenderer::createView(EngineShared pEngine)
{
  return ViewUnique(pEngine->createView(), FilamentComponentCleaner(pEngine));
}

CCameraUnique
CFilamentRenderer::createCamera(EngineShared pEngine)
{
  const auto cameraId = utils::EntityManager::get().create();
  const auto pCamera = pEngine->createCamera(cameraId);
  return CCameraUnique(new CCamera(pCamera, cameraId),
                       FilamentComponentCleaner(pEngine));
}

SceneUnique
CFilamentRenderer::createScene(EngineShared pEngine)
{
  return SceneUnique(pEngine->createScene(), FilamentComponentCleaner(pEngine));
}

SkyboxUnique
CFilamentRenderer::createSkybox(EngineShared pEngine)
{
  return SkyboxUnique(
    Skybox::Builder().color({ 0.1, 0.125, 0.25, 1.0 }).build(*pEngine),
    FilamentComponentCleaner(pEngine));
}

VertexBufferUnique
CFilamentRenderer::createVertexBuffer(EngineShared pEngine)
{
  const auto pVertexBuffer =
    VertexBuffer::Builder()
      .vertexCount(3)
      .bufferCount(1)
      .attribute(VertexAttribute::POSITION,
                 0,
                 VertexBuffer::AttributeType::FLOAT2,
                 0,
                 12)
      .attribute(
        VertexAttribute::COLOR, 0, VertexBuffer::AttributeType::UBYTE4, 8, 12)
      .normalized(VertexAttribute::COLOR)
      .build(*pEngine);

  return VertexBufferUnique(pVertexBuffer, FilamentComponentCleaner(pEngine));
}

IndexBufferUnique
CFilamentRenderer::createIndexBuffer(EngineShared pEngine)
{
  const auto pIndexBuffer = IndexBuffer::Builder()
                              .indexCount(3)
                              .bufferType(IndexBuffer::IndexType::USHORT)
                              .build(*pEngine);
  return IndexBufferUnique(pIndexBuffer, FilamentComponentCleaner(pEngine));
}

EntityUnique
CFilamentRenderer::createRenderable(EngineShared pEngine,
                                    const filament::VertexBuffer*,
                                    const filament::IndexBuffer*)
{
  const auto renderable = utils::EntityManager::get().create();
  RenderableManager::Builder(1)
    .boundingBox({ { -1, -1, -1 }, { 1, 1, 1 } })
    .material(0, m_pMaterial->getDefaultInstance())
    .geometry(0,
              RenderableManager::PrimitiveType::TRIANGLES,
              m_pVertexBuffer.get(),
              m_pIndexBuffer.get(),
              0,
              3)
    .culling(false)
    .receiveShadows(false)
    .castShadows(false)
    .build(*pEngine, renderable);

  return EntityUnique(new CEntity(renderable),
                      FilamentComponentCleaner(pEngine));
}

MaterialUnique
CFilamentRenderer::createMaterial(EngineShared pEngine)
{
  return MaterialUnique(
    Material::Builder()
      .package(RESOURCES_BAKEDCOLOR_DATA, RESOURCES_BAKEDCOLOR_SIZE)
      .build(*pEngine),
    FilamentComponentCleaner(pEngine));
}

CameraManipulatorUnique
CFilamentRenderer::createCameraManipulator(
  const MathTypes::UIntSize2D& windowSize)
{
  return CameraManipulatorUnique(CameraManipulator::Builder()
                                   .viewport(windowSize.x(), windowSize.y())
                                   .targetPosition(0, 0, -10)
                                   .flightMoveDamping(15.0)
                                   .build(filament::camutils::Mode::ORBIT));
}

void
CFilamentRenderer::execute()
{
  if (m_pRenderer->beginFrame(m_pSwapChain.get())) {
    m_pRenderer->render(m_pMainView.get());
    m_pRenderer->endFrame();
  }
}

COperator&
CFilamentRenderer::cameraOperator()
{
  return *m_pOperator.get();
}
