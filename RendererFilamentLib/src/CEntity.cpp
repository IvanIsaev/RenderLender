#include "CEntity.h"

using namespace RendererFilament;

CEntity::CEntity(utils::Entity entity)
  : m_entity(entity)
{
}

const utils::Entity&
CEntity::entityId() const
{
  return m_entity;
}
