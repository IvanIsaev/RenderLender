#pragma once

#include "CFilamentComponentCleaner.h"

#include <memory>

namespace filament {
namespace camutils {
template<typename T>
class Manipulator;
}
}

namespace RendererFilament {
class CCamera;

using CameraManipulator = filament::camutils::Manipulator<float>;
using CameraManipulatorUnique = std::unique_ptr<CameraManipulator>;

using CCameraUnique = std::unique_ptr<CCamera, FilamentComponentCleaner>;
}