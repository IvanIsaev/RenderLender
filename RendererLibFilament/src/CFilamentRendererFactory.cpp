#include "CFilamentRendererFactory.h"
#include "CFilamentRendererFacade.h"

std::unique_ptr<IRendererFacade>
CFilamentRendererFactory::create()
{
  return std::make_unique<CFilamentRendererFacade>();
  ;
}