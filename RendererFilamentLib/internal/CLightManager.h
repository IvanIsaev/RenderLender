#pragma once

#include "CEntity.h"
#include "FilamentTypesFwd.h"

#include <vector>

namespace RendererFilament {
class CLightManager
{
public:
  explicit CLightManager(EngineShared, filament::Scene&);

private:
  EngineShared m_pEngine;
  filament::Scene& m_scene;

  std::vector<EntityUnique> m_lightSources;
};
}