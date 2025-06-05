#include "CLightManager.h"

#include <filament/LightManager.h>
#include <filament/Scene.h>

#include <utils/EntityManager.h>

RendererFilament::CLightManager::CLightManager(EngineShared pEngine,
                                               filament::Scene& scene)
  : m_pEngine{ pEngine }
  , m_scene{ scene }
{
    using namespace filament;

  auto sun = utils::EntityManager::get().create();
  LightManager::Builder(LightManager::Type::SUN)
    .color(Color::toLinear<ACCURATE>(sRGBColor(0.98f, 0.92f, 0.89f)))
    .intensity(1100000)
    .direction({ 0.7, -1, -0.8 })
    .position({ 0, 2, 0 })
    .sunAngularRadius(1.9f)
    .castShadows(true)
    .build(*m_pEngine.get(), sun);

  m_scene.addEntity(sun);

  m_lightSources.emplace_back(new CEntity(sun),
                              FilamentComponentCleaner{ m_pEngine });
}