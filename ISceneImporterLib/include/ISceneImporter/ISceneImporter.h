#pragma once

#include <Scene/Scene.h>

#include <memory>

class ISceneImporter
{
public:
  virtual ~ISceneImporter() = default;

  virtual SceneUnique import() const = 0;
};

using ISceneImporterUnique = std::unique_ptr<ISceneImporter>;
