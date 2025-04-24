#include "CFilamentComponentCleaner.h"
#include "CCamera.h"
#include "CEntity.h"

#include <utils/EntityManager.h>

FilamentComponentCleaner::FilamentComponentCleaner(EngineShared pEngine)
  : m_pEngine(pEngine)
{
}

void
FilamentComponentCleaner::operator()(CCamera* pCamera)
{
  m_pEngine->destroyCameraComponent(pCamera->entityId());
  utils::EntityManager::get().destroy(pCamera->entityId());
}

void
FilamentComponentCleaner::operator()(CEntity* pEntity)
{
  m_pEngine->destroy(pEntity->entityId());
}