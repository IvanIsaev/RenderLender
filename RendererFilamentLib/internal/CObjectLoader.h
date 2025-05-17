#pragma once

#include "CEntity.h"
#include "CIndexBufferManager.h"
#include "CVertexBufferManager.h"
#include "FilamentEngineFwd.h"
#include "FilamentTypesFwd.h"

#include "IRenderer/IObjectLoader.h"

namespace filament {
class IndexBuffer;
class Scene;
class VertexBuffer;
}

namespace RendererFilament {
class CObjectLoader : public IRenderer::IObjectLoader
{
public:
  explicit CObjectLoader(EngineShared, filament::Scene&);

  void loadObject(const IRenderer::Object&) override;
  std::optional<uint32_t> idLastLoadedObject() const override;

private:
  VertexBufferUnique createVertexBuffer(EngineShared,
                                        const IRenderer::Vertices&);

  IndexBufferUnique createIndexBuffer(EngineShared, const IRenderer::Faces&);

  EntityUnique createRenderable(EngineShared,
                                filament::VertexBuffer*,
                                filament::IndexBuffer*,
                                const IRenderer::Faces&);

  MaterialUnique createMaterial(EngineShared);


private:
  VertexBufferManagerShared m_pVertexBufferManager;
  IndexBufferManagerShared m_pIndexBufferManager;
  EngineShared m_pEngine;
  filament::Scene& m_scene;
  MaterialUnique m_pDefaultMaterial;
  std::optional<uint32_t> m_idLastAddedObject;
  std::vector<std::unique_ptr<IRenderer::Object>> m_objectsForDelete;
  std::vector<EntityUnique> m_renderables;
};
}