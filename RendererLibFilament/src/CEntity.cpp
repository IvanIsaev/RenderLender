#include "CEntity.h"

CEntity::CEntity(utils::Entity entity)
  : m_entity(entity)
{
}

const utils::Entity&
CEntity::entityId() const
{
  return m_entity;
}
