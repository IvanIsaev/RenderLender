#include "CFilamentRenderer.h"

#include <filament/Engine.h>
#include <backend/DriverEnums.h>

using namespace filament;

CFilamentRenderer::CFilamentRenderer ( )
{
}

bool CFilamentRenderer::execute ( )
{
    Engine::Config engineConfig = {};
    engineConfig.stereoscopicEyeCount = 2;
    engineConfig.stereoscopicType = Engine::StereoscopicType::NONE;

    auto pEngine = Engine::Builder ( )
        .backend ( backend::Backend::DEFAULT )
        .featureLevel ( backend::FeatureLevel::FEATURE_LEVEL_3 )
        .config ( &engineConfig ).build ( );

    Engine::destroy ( &pEngine );

    return false;
}
