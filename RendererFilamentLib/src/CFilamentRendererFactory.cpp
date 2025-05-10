#include "RendererFilament/CFilamentRendererFactory.h"
#include "CFilamentRendererFacade.h"

using namespace RendererFilament;

std::unique_ptr<IRenderer::IRendererFacade>
CFilamentRendererFactory::create()
{
  return std::make_unique<CFilamentRendererFacade>();
}