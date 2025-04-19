#pragma once

#include "FilamentComponentCleaner.h"

#include <utils/Entity.h>

class CEntity
{
public:
  CEntity(utils::Entity);

  const utils::Entity& entityId() const;

private:
  const utils::Entity m_entity;
};

