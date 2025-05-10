#pragma once

#include <MathTypes/Matrix.h>

#include <assimp/matrix4x4.h>

namespace SceneImporter
{
MathTypes::FloatMatrix4x4
convertMatrix(const aiMatrix4x4& mat);
}