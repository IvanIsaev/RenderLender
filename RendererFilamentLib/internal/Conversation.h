#pragma once

#include <MathTypes/Matrix.h>

#include <math/mat4.h>

namespace RendererFilament {
filament::math::mat4f
convertToFilamentMat(const MathTypes::FloatMatrix4x4&);
}