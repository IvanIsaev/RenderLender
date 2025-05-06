#include "SceneImporter/CSceneImporterFactory.h"

#include "CAssimpSceneImporter.h"

CSceneImporterFactory::CSceneImporterFactory(
  const std::string& absolutePathToFile)
  : m_absolutePathToFile(absolutePathToFile)
{
}

ISceneImporterUnique
CSceneImporterFactory::create() const
{
  return std::make_unique<CAssimpSceneImporter>(m_absolutePathToFile);
}