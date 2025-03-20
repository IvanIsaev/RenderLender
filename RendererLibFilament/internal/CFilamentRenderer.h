#pragma once

#include <IRenderer.h>

#include <memory>

namespace filament {
class Engine;
class Scene;
}

class CFilamentRenderer : public IRenderer
{
public:
  CFilamentRenderer();
  ~CFilamentRenderer();

  IEventWindow& eventWindow() override;

  bool execute() override;

private:
  filament::Engine* m_pEngine;
  std::unique_ptr<IEventWindow> m_pEventWindow;
};