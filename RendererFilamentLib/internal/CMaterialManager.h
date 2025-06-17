#pragma once

#include "FilamentEngineFwd.h"
#include "FilamentTypesFwd.h"

#include <IRenderer/IMaterialManager.h>

#include <utils/Entity.h>

namespace RendererFilament {
class CMaterialManager : public IRenderer::IMaterialManager
{
public:
  explicit CMaterialManager(EngineShared);
  void init();

  uint32_t defaultMaterialInstanceId() const override;

  filament::MaterialInstance* getMaterialInstance(uint32_t) const;

private:
  EngineShared m_pEngine;

  MaterialUnique m_pDefaultMaterial;
  MaterialInstanceUnique m_pMaterialInstance;
  utils::Entity m_materialInstanceId;
};
}