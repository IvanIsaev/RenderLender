#include <CFilamentRenderer.h>

#include <DeleteMe.h>

#include <backend/BufferDescriptor.h>
#include <backend/DriverEnums.h>
#include <camutils/Manipulator.h>
#include <filament/Camera.h>
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

#include <math/vec2.h>

#include <utils/EntityManager.h>

#include <cmath>
#include <numbers>

using namespace filament;

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
  , m_pRenderer(nullptr)
  , m_pSwapChain(nullptr)
  , m_pMainView(nullptr)
  , m_pScene(nullptr)
  , m_pSkybox(nullptr)
  , m_pVertexBuffer(nullptr)
  , m_pIndexBuffer(nullptr)
  , m_pMaterial(nullptr)
  , m_pCamera(nullptr)
  , m_pCameraManipulator(nullptr)
  , m_mouseCursorHandler(std::make_unique<CMouseCursorHandler>())
{
}

CFilamentRenderer::~CFilamentRenderer()
{
  m_pEngine->destroy(m_pRenderer);
  m_pEngine->destroy(m_pSwapChain);
  m_pEngine->destroyCameraComponent(m_cameraId);
  utils::EntityManager::get().destroy(m_cameraId);
  m_pEngine->destroy(m_pMainView);
  m_pEngine->destroy(m_pScene);
  m_pEngine->destroy(m_pSkybox);
  m_pEngine->destroy(m_pVertexBuffer);
  m_pEngine->destroy(m_pIndexBuffer);
  m_pEngine->destroy(m_renderable);
  m_pEngine->destroy(m_pMaterial);

  delete m_pCameraManipulator;

  Engine::destroy(&m_pEngine);
}

void
CFilamentRenderer::init(const Config& settings)
{
  const auto engineConfig = Engine::Config{};

  m_pEngine = Engine::Builder()
                .backend(backend::Backend::VULKAN)
                .featureLevel(backend::FeatureLevel::FEATURE_LEVEL_3)
                .config(&engineConfig)
                .build();

  m_pSwapChain = m_pEngine->createSwapChain(
    settings.nativeWindow, filament::SwapChain::CONFIG_HAS_STENCIL_BUFFER);

  m_pRenderer = m_pEngine->createRenderer();

  m_pMainView = m_pEngine->createView();

  configureViewport(settings);

  m_pCameraManipulator =
    CameraManipulator::Builder()
      .viewport(settings.windowSize.width, settings.windowSize.height)
      .targetPosition(0, 0, -4)
      .flightMoveDamping(15.0)
      .build(filament::camutils::Mode::ORBIT);
  m_mouseCursorHandler->setRenderer(this);
  m_mouseCursorHandler->setCameraManipulator(m_pCameraManipulator);

  m_pScene = m_pEngine->createScene();

  m_pMainView->setVisibleLayers(0x4, 0x4); // Magic numbers
  m_pMainView->setScene(m_pScene);

  setup();
}

IMouseCursorHandler*
CFilamentRenderer::mouseCursorHandler()
{
  return m_mouseCursorHandler.get();
}

void
CFilamentRenderer::setup()
{
  m_pSkybox =
    Skybox::Builder().color({ 0.1, 0.125, 0.25, 1.0 }).build(*m_pEngine);

  m_pScene->setSkybox(m_pSkybox);

  m_pMainView->setPostProcessingEnabled(false);

  m_pVertexBuffer =
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
      .build(*m_pEngine);
  m_pVertexBuffer->setBufferAt(
    *m_pEngine,
    0,
    VertexBuffer::BufferDescriptor(TRIANGLE_VERTICES, 36, nullptr));

  m_pIndexBuffer = IndexBuffer::Builder()
                     .indexCount(3)
                     .bufferType(IndexBuffer::IndexType::USHORT)
                     .build(*m_pEngine);
  m_pIndexBuffer->setBuffer(
    *m_pEngine, IndexBuffer::BufferDescriptor(TRIANGLE_INDICES, 6, nullptr));

  m_pMaterial = Material::Builder()
                  .package(RESOURCES_BAKEDCOLOR_DATA, RESOURCES_BAKEDCOLOR_SIZE)
                  .build(*m_pEngine);

  m_renderable = utils::EntityManager::get().create();
  const auto result = RenderableManager::Builder(1)
                        .boundingBox({ { -1, -1, -1 }, { 1, 1, 1 } })
                        .material(0, m_pMaterial->getDefaultInstance())
                        .geometry(0,
                                  RenderableManager::PrimitiveType::TRIANGLES,
                                  m_pVertexBuffer,
                                  m_pIndexBuffer,
                                  0,
                                  3)
                        .culling(false)
                        .receiveShadows(false)
                        .castShadows(false)
                        .build(*m_pEngine, m_renderable);

  auto& transformManager = m_pEngine->getTransformManager();
  auto ti = transformManager.getInstance(m_renderable);
  filament::math::mat4f transform = filament::math::mat4f{
    filament::math::mat3f(1), filament::math::float3(0, 0, -4)
  } * transformManager.getWorldTransform(ti);

  m_pScene->addEntity(m_renderable);
  transformManager.setTransform(ti, transform);
}

void
CFilamentRenderer::configureViewport(const Config& config)
{
  const uint32_t width = config.windowSize.width;
  const uint32_t height = config.windowSize.height;

  auto aspectRatio = double(width) / height;

  m_cameraId = utils::EntityManager::get().create();
  m_pCamera = m_pEngine->createCamera(m_cameraId);
  m_pCamera->setLensProjection(28, 1.0, 0.1, 100.0);
  m_pCamera->setScaling({ 1.0 / aspectRatio, 1.0 });
  m_pMainView->setCamera(m_pCamera);
  m_pMainView->setViewport({ 0, 0, width, height });
}

bool
CFilamentRenderer::execute()
{
  filament::math::float3 eye, center, up;
  m_pCameraManipulator->getLookAt(&eye, &center, &up);
  m_pCamera->lookAt(eye, center, up);

  if (m_pRenderer->beginFrame(m_pSwapChain)) {
    m_pRenderer->render(m_pMainView);
    m_pRenderer->endFrame();
  }
  return true;
}
