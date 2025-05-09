#pragma once

#include "rendererfilamentlib_export.h"

#include <IRenderer/IRendererFacade.h>

#include <memory>

class RENDERERFILAMENTLIB_EXPORT CFilamentRendererFactory
{
public:
  static std::unique_ptr<IRendererFacade> create();
};
