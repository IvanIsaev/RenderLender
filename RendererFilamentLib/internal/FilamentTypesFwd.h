#pragma once

#include "CameraFwd.h"
#include "FilamentEngineFwd.h"

#include <memory>

class CCamera;
class CEntity;
class COperator;
class FilamentComponentCleaner;

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

namespace utils {
class Entity;
}

using RendererUnique = std::unique_ptr<filament::Renderer, FilamentComponentCleaner>;
using SwapChainUnique = std::unique_ptr<filament::SwapChain, FilamentComponentCleaner>;
using ViewUnique = std::unique_ptr<filament::View, FilamentComponentCleaner>;
using SceneUnique = std::unique_ptr<filament::Scene, FilamentComponentCleaner>;
using SkyboxUnique = std::unique_ptr<filament::Skybox, FilamentComponentCleaner>;
using VertexBufferUnique = std::unique_ptr<filament::VertexBuffer, FilamentComponentCleaner>;
using IndexBufferUnique = std::unique_ptr<filament::IndexBuffer, FilamentComponentCleaner>;
using EntityUnique = std::unique_ptr<CEntity, FilamentComponentCleaner>;
using MaterialUnique = std::unique_ptr<filament::Material, FilamentComponentCleaner>;
using OperatorUnique = std::unique_ptr<COperator>;
