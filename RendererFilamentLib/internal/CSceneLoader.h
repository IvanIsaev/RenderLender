#pragma once

#include <functional>

namespace RendererFilament {
class CMaterialManager;
struct Object;
}

namespace Scene {
struct Scene;
}

namespace RendererFilament {
class CSceneLoader
{
public:
  explicit CSceneLoader(const CMaterialManager&);

  void operator()(const Scene::Scene&, const std::function<uint32_t(const Object&)>& loader) const;

private:
  const CMaterialManager& m_materialManager;
};
}