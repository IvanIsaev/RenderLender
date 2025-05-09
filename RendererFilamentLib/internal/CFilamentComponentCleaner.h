#pragma once

#include "FilamentEngineFwd.h"

#include <filament/Engine.h>

namespace RendererFilament {
class CCamera;
class CEntity;
}

namespace RendererFilament {
class FilamentComponentCleaner
{
public:
  explicit FilamentComponentCleaner(EngineShared pEngine);

  template<typename T>
  void operator()(T* ptr)
  {
    m_pEngine->destroy(ptr);
  }

  void operator()(CCamera*);
  void operator()(CEntity*);

private:
  EngineShared m_pEngine;
};
}