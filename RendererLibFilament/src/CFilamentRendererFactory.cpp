#include <CFilamentRendererFactory.h>

#include <CFilamentRenderer.h>

std::unique_ptr<IRenderer>
CFilamentRendererFactory::create()
{
  return std::make_unique<CFilamentRenderer>();
  ;
}