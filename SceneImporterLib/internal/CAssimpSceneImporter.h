#pragma once

#include "sceneimporterlib_export.h"

#include <ISceneImporter/ISceneImporter.h>

#include <Scene/Scene.h>

#include <assimp/scene.h>

#include <string>

class CAssimpSceneImporter : public ISceneImporter::ISceneImporter
{
public:
  explicit CAssimpSceneImporter(const std::string&);

  Scene::SceneUnique import() const override;

private:
  const std::string m_absolutePathToFile;
};