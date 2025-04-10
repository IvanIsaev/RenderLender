#pragma once

#include <IRenderer.h>
#include <CMouseCursorHandler.h>

#include <utils/Entity.h>

#include <memory>

namespace filament {
class Camera;
class Engine;
class IndexBuffer;
class Material;
class MaterialInstance;
class Renderer;
class Scene;
class Skybox;
class SwapChain;
class VertexBuffer;
class View;

namespace camutils {
template<typename T>
class Manipulator;
}
}

class CFilamentRenderer : public IRenderer
{
  using CameraManipulator = filament::camutils::Manipulator<float>;

public:
  CFilamentRenderer();
  ~CFilamentRenderer();

  void init(const Config&) override;

  IMouseCursorHandler* mouseCursorHandler() override;

  bool execute() override;

private:
  void setup();

  void configureViewport(const Config&);

private:
  filament::Engine* m_pEngine;
  filament::Renderer* m_pRenderer;
  filament::SwapChain* m_pSwapChain;
  filament::View* m_pMainView;
  filament::Scene* m_pScene;
  filament::Skybox* m_pSkybox;
  filament::VertexBuffer* m_pVertexBuffer;
  filament::IndexBuffer* m_pIndexBuffer;
  utils::Entity m_renderable;
  filament::Material* m_pMaterial;
  filament::Camera* m_pCamera;
  utils::Entity m_cameraId;

  CameraManipulator* m_pCameraManipulator;

  std::unique_ptr<CMouseCursorHandler> m_mouseCursorHandler;
};