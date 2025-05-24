#pragma once

#include "CFilamentComponentCleaner.h"
#include "CIndexBufferManager.h"
#include "CMouseCursorHandler.h"
#include "CVertexBufferManager.h"
#include "FilamentEngineFwd.h"
#include "FilamentTypesFwd.h"

#include <IRenderer/Object.h>
#include <IRenderer/RenderConfig.h>

namespace RendererFilament {

class CFilamentRenderer
{
public:
  CFilamentRenderer();
  ~CFilamentRenderer();

  void init(const IRenderer::RenderConfig&);

  void execute();

  COperator& cameraOperator();

  EngineShared engine() const;

  filament::Scene& scene();

private:
  EngineShared createEngine() const;
  RendererUnique createRenderer(EngineShared);
  SwapChainUnique createSwapChain(EngineShared, void*);
  ViewUnique createView(EngineShared);
  CCameraUnique createCamera(EngineShared);
  SceneUnique createScene(EngineShared);
  SkyboxUnique createSkybox(EngineShared);
  CameraManipulatorUnique createCameraManipulator(const MathTypes::UIntSize2D&);

private:
  EngineShared m_pEngine;
  RendererUnique m_pRenderer;
  SwapChainUnique m_pSwapChain;
  ViewUnique m_pMainView;
  SceneUnique m_pScene;
  SkyboxUnique m_pSkybox;
  OperatorUnique m_pOperator;
};
}