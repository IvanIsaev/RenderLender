#pragma once

#include "sceneimporterlib_export.h"

#include <ISceneImporter/ISceneImporter.h>

#include <string>

class CSceneImporterFactory
{
public:
  SCENEIMPORTERLIB_EXPORT explicit CSceneImporterFactory(const std::string&);
  SCENEIMPORTERLIB_EXPORT ~CSceneImporterFactory() = default;

  SCENEIMPORTERLIB_EXPORT ISceneImporter::ISceneImporterUnique create() const;

private:
  const std::string m_absolutePathToFile;
};