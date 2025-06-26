#pragma once

#include <MathTypes/Matrix.h>
#include <MathTypes/Point.h>

#include <math/mat4.h>
#include <math/vec3.h>

namespace RendererFilament {
filament::math::mat4f
convertToFilamentMat(const MathTypes::FloatMatrix4x4&);

filament::math::float3
convertToFilamentVector(const MathTypes::FloatPoint3D&);
}