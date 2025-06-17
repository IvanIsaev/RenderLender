#include "CMaterialManager.h"
#include "DeleteMe.h"

#include <filament/Material.h>
#include <filament/MaterialInstance.h>

#include <utils/EntityManager.h>


using namespace RendererFilament;

namespace
{
MaterialUnique
createDefaultMaterial(EngineShared pEngine)
{
  using namespace filament;

  return MaterialUnique(
    Material::Builder()
      .package(RESOURCES_AIDEFAULTMAT_DATA, RESOURCES_AIDEFAULTMAT_SIZE)
      .build(*pEngine),
    FilamentComponentCleaner(pEngine));
}

MaterialInstanceUnique
createDefaultMaterialInstance(const filament::Material& material,
                              EngineShared pEngine)
{
  auto mi = material.createInstance();
  mi->setParameter(
    "baseColor", filament::RgbType::LINEAR, filament::math::float3{ 0.8 });
  mi->setParameter("metallic", 1.0f);
  mi->setParameter("roughness", 0.4f);
  mi->setParameter("reflectance", 0.5f);

  return MaterialInstanceUnique(mi, FilamentComponentCleaner(pEngine));
}
}

CMaterialManager::CMaterialManager(EngineShared pEngine)
  : m_pEngine(pEngine)
  , m_pDefaultMaterial(nullptr, FilamentComponentCleaner(nullptr))
  , m_pMaterialInstance(nullptr, FilamentComponentCleaner(nullptr))
{
}

void
CMaterialManager::init()
{
  m_pDefaultMaterial = createDefaultMaterial(m_pEngine);
  m_pMaterialInstance =
    createDefaultMaterialInstance(*m_pDefaultMaterial.get(), m_pEngine);

  m_materialInstanceId = utils::EntityManager::get().create();
}

uint32_t
CMaterialManager::defaultMaterialInstanceId() const
{
  return m_materialInstanceId.getId();
}

filament::MaterialInstance*
RendererFilament::CMaterialManager::getMaterialInstance(uint32_t) const
{
  return m_pMaterialInstance.get();
}


