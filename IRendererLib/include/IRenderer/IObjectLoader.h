#pragma once

namespace Scene
{
struct Scene;
}

namespace IRenderer {
class IObjectLoader
{
public:
  virtual ~IObjectLoader() = default;

  virtual void load(const Scene::Scene& scene) = 0;
};
}