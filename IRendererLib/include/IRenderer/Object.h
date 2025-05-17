#pragma once

#include "Mesh.h"

#include <MathTypes/Matrix.h>
#include <MathTypes/Point.h>

#include <optional>
#include <vector>

namespace IRenderer {
struct Object
{
  std::vector<Mesh> meshes;
  MathTypes::FloatMatrix4x4 transformation;
  std::optional<uint32_t> parent_id;
};
}