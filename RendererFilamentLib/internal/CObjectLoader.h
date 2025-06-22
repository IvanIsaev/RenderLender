#pragma once

#include "CEntity.h"
#include "CIndexBufferManager.h"
#include "CVertexBufferManager.h"
#include "FilamentEngineFwd.h"
#include "FilamentTypesFwd.h"

#include "Scene/Object.h"

#include "IRenderer/IObjectLoader.h"

namespace filament {
class IndexBuffer;
class Scene;
class VertexBuffer;
}

namespace RendererFilament {
class CMaterialManager;
}

namespace RendererFilament {
class CObjectLoader : public IRenderer::IObjectLoader
{
public:
  explicit CObjectLoader(EngineShared, filament::Scene&, CMaterialManager&);

  void load(const Scene::Scene& scene) override;

private:
  VertexBufferUnique createVertexBuffer(EngineShared,
                                        const Vertices&);

  IndexBufferUnique createIndexBuffer(EngineShared,
                                      const Faces&);

  EntityUnique createRenderable(EngineShared,
                                filament::VertexBuffer*,
                                filament::IndexBuffer*,
                                const Faces&,
                                uint32_t);

  uint32_t load(const Object&);

private:
  VertexBufferManagerShared m_pVertexBufferManager;
  IndexBufferManagerShared m_pIndexBufferManager;
  EngineShared m_pEngine;
  filament::Scene& m_scene;
  std::vector<std::unique_ptr<Object>> m_objectsForDelete;
  std::vector<EntityUnique> m_renderables;
  CMaterialManager& m_materialManager;
};
}