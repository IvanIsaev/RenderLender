#include <CFilamentRenderer.h>

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

bool CFilamentRenderer::execute ( )
{ 
    return false;
}
