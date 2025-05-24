#include "CFilamentRenderer.h"
#include "CCamera.h"
#include "COperator.h"

#include <backend/DriverEnums.h>
#include <camutils/Manipulator.h>
#include <filament/Engine.h>
#include <filament/Renderer.h>
#include <filament/Scene.h>
#include <filament/Skybox.h>
#include <filament/SwapChain.h>
#include <filament/View.h>
#include <filament/ViewPort.h>

#include <utils/EntityManager.h>

#include <cmath>
#include <numbers>

using namespace filament;
using namespace RendererFilament;

CFilamentRenderer::CFilamentRenderer()
  : m_pEngine(nullptr)
  , m_pRenderer(nullptr, FilamentComponentCleaner(nullptr))
  , m_pSwapChain(nullptr, FilamentComponentCleaner(nullptr))
  , m_pMainView(nullptr, FilamentComponentCleaner(nullptr))
  , m_pScene(nullptr, FilamentComponentCleaner(nullptr))
  , m_pSkybox(nullptr, FilamentComponentCleaner(nullptr))
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

CameraManipulatorUnique
CFilamentRenderer::createCameraManipulator(
  const MathTypes::UIntSize2D& windowSize)
{
  return CameraManipulatorUnique(CameraManipulator::Builder()
                                   .viewport(windowSize.x(), windowSize.y())
                                   .targetPosition(0, 0, 0)
                                   .flightMoveDamping(15.0)
                                   .orbitHomePosition(0, 0, 20)
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

EngineShared
RendererFilament::CFilamentRenderer::engine() const
{
  return m_pEngine;
}

filament::Scene&
RendererFilament::CFilamentRenderer::scene()
{
  return *m_pScene.get();
}
