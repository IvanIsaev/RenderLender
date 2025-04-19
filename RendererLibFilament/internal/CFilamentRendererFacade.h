#pragma once

#include "CFilamentRenderer.h"
#include "CMouseCursorHandler.h"

#include <IRendererFacade.h>

#include <memory>

class CFilamentRendererFacade : public IRendererFacade
{
public:
  CFilamentRendererFacade();
  ~CFilamentRendererFacade() = default;

  void init(const RenderConfig&) override;

  IMouseCursorHandler* mouseCursorHandler() override;

  void execute() override;

private:
  std::unique_ptr<CFilamentRenderer> m_pFilamentRenderer;
  std::unique_ptr<CMouseCursorHandler> m_pMouseCursorHandler;
};