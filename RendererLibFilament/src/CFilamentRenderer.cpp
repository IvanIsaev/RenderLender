#include <CFilamentRenderer.h>

#include <CEventWindow.h>

#include <filament/Engine.h>
#include <backend/DriverEnums.h>


using namespace filament;

CFilamentRenderer::CFilamentRenderer ( ) : m_pEngine ( nullptr )
{
    Engine::Config engineConfig = {};

    m_pEngine = Engine::Builder ( )
        .backend ( backend::Backend::VULKAN )
        .config ( &engineConfig ).build ( );    
}

CFilamentRenderer::~CFilamentRenderer ( )
{ 
    Engine::destroy ( &m_pEngine );
}

IEventWindow&
CFilamentRenderer::eventWindow()
{
  if (!m_pEventWindow)
    m_pEventWindow = std::make_unique<CEventWindow>();

  return *m_pEventWindow;
}

bool CFilamentRenderer::execute ( )
{ 
    return false;
}
