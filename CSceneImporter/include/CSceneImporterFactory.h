#pragma once

#include "assimplib_export.h"

#include <ISceneImporter.h>

#include <string>

class CSceneImporterFactory
{
public:
  ASSIMPLIB_EXPORT explicit CSceneImporterFactory(const std::string&);

  ASSIMPLIB_EXPORT ISceneImporterUnique create() const;

private:
  const std::string m_absolutePathToFile;
};