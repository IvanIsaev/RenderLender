#pragma once

#include "rendererlib_export.h"

#include <IRendererFacade.h>

#include <memory>

class RENDERERLIB_EXPORT CFilamentRendererFactory
{
public:
  static std::unique_ptr<IRendererFacade> create();
};
