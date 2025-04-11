#pragma once

#include "FilamentComponentCleaner.h"

#include <memory>

class CCamera;

namespace filament {
namespace camutils {
template<typename T>
class Manipulator;
}
}

using CameraManipulator = filament::camutils::Manipulator<float>;
using CameraManipulatorUnique = std::unique_ptr<CameraManipulator>;

using CCameraUnique = std::unique_ptr<CCamera, FilamentComponentCleaner>;