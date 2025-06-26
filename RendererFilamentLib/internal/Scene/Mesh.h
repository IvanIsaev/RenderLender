#pragma once

#include "Color.h"

#include <MathTypes/Matrix.h>
#include <MathTypes/Point.h>

#include <math/vec4.h>

#include <vector>

namespace RendererFilament {
struct Face;

using Point3D = MathTypes::FloatPoint3D;
using TBN = filament::math::short4; // Tangent bitangent normal represented as quaternion
using Faces = std::vector<Face>;

struct Face
{
  unsigned int a;
  unsigned int b;
  unsigned int c;
};

struct Vertices
{
  std::vector<Point3D> coords;
  std::vector<Color> colors;
  std::vector<TBN> tbn;
};

struct Mesh
{
  Faces faces;
  Vertices vertices;
  uint32_t materialIndex;
};

static constexpr auto sizeOfCoord = sizeof(Point3D);
static constexpr auto sizeOfFace = sizeof(Face);
static constexpr auto sizeOfTBN = sizeof(TBN);
}