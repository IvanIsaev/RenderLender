#pragma once

#include <Scene/Scene.h>

#include <memory>

namespace ISceneImporter {
class ISceneImporter
{
public:
  virtual ~ISceneImporter() = default;

  virtual Scene::SceneUnique import() const = 0;
};

using ISceneImporterUnique = std::unique_ptr<ISceneImporter>;
}