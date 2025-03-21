#include <CFilamentRenderer.h>

#include <CEventWindow.h>

#include <backend/DriverEnums.h>
#include <filament/Engine.h>
#include <filament/Renderer.h>
#include <filament/SwapChain.h>

using namespace filament;

CFilamentRenderer::CFilamentRenderer()
  : m_pEngine(nullptr)
  , m_pRenderer(nullptr)
  , m_pSwapChain(nullptr)
{
}

CFilamentRenderer::~CFilamentRenderer()
{
  m_pEngine->destroy(m_pRenderer);
  m_pEngine->destroy(m_pSwapChain);

  Engine::destroy(&m_pEngine);
}

void
CFilamentRenderer::init(const Config& settings)
{
  Engine::Config engineConfig = {};

  m_pEngine = Engine::Builder()
                .backend(backend::Backend::VULKAN)
                .config(&engineConfig)
                .build();

  m_pSwapChain = m_pEngine->createSwapChain(
    settings.nativeWindow, filament::SwapChain::CONFIG_HAS_STENCIL_BUFFER);

  m_pRenderer = m_pEngine->createRenderer();
}

IEventWindow&
CFilamentRenderer::eventWindow()
{
  if (!m_pEventWindow)
    m_pEventWindow = std::make_unique<CEventWindow>();

  return *m_pEventWindow;
}

bool
CFilamentRenderer::execute()
{
  return false;
}
