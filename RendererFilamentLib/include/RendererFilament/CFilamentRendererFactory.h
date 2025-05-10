#pragma once

#include "rendererfilamentlib_export.h"

#include <IRenderer/IRendererFacade.h>

#include <memory>

namespace RendererFilament {
class RENDERERFILAMENTLIB_EXPORT CFilamentRendererFactory
{
public:
  static std::unique_ptr<IRenderer::IRendererFacade> create();
};
}