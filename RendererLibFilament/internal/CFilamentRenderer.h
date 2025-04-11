#pragma once

#include "CMouseCursorHandler.h"
#include "FilamentComponentCleaner.h"
#include "FilamentEngineFwd.h"
#include "FilamentTypesFwd.h"

#include <RenderConfig.h>

class CFilamentRenderer
{
public:
  CFilamentRenderer();
  ~CFilamentRenderer();

  void init(const RenderConfig&);

  void execute();

  COperator& cameraOperator();

private:
  EngineShared createEngine() const;
  RendererUnique createRenderer(EngineShared);
  SwapChainUnique createSwapChain(EngineShared, void*);
  ViewUnique createView(EngineShared);
  CCameraUnique createCamera(EngineShared);
  SceneUnique createScene(EngineShared);
  SkyboxUnique createSkybox(EngineShared);
  VertexBufferUnique createVertexBuffer(EngineShared);
  IndexBufferUnique createIndexBuffer(EngineShared);
  EntityUnique createRenderable(EngineShared,
                                const filament::VertexBuffer*,
                                const filament::IndexBuffer*);
  MaterialUnique createMaterial(EngineShared);
  CameraManipulatorUnique createCameraManipulator(const IntSize2D&);

private:
  EngineShared m_pEngine;
  RendererUnique m_pRenderer;
  SwapChainUnique m_pSwapChain;
  ViewUnique m_pMainView;
  SceneUnique m_pScene;
  SkyboxUnique m_pSkybox;
  VertexBufferUnique m_pVertexBuffer;
  IndexBufferUnique m_pIndexBuffer;
  EntityUnique m_pRenderable;
  MaterialUnique m_pMaterial;
  OperatorUnique m_pOperator;
};