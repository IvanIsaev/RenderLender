#pragma once

#include <IRenderer.h>

#include <memory>

namespace filament {
class Engine;
class Renderer;
class Scene;
}

class CFilamentRenderer : public IRenderer
{
public:
  CFilamentRenderer();
  ~CFilamentRenderer();

  void init(const Config&) override;

  IEventWindow& eventWindow() override;

  bool execute() override;

private:
  filament::Engine* m_pEngine;
  filament::Renderer* m_pRenderer;

  std::unique_ptr<IEventWindow> m_pEventWindow;
};