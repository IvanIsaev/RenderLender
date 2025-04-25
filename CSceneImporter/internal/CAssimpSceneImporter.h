#pragma once

#include "assimplib_export.h"

#include <ISceneImporter.h>

#include <Scene.h>

#include <assimp/scene.h>

#include <string>

class CAssimpSceneImporter : public ISceneImporter
{
public:
  explicit CAssimpSceneImporter(const std::string&);

  SceneUnique import() const override;

private:
  const std::string m_absolutePathToFile;
};