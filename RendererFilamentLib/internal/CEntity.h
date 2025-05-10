#pragma once

#include "CFilamentComponentCleaner.h"

#include <utils/Entity.h>

namespace RendererFilament {
class CEntity
{
public:
  CEntity(utils::Entity);

  const utils::Entity& entityId() const;

private:
  const utils::Entity m_entity;
};
}