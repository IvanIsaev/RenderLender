#pragma once

#include "Color.h"

#include <MathTypes/Matrix.h>
#include <MathTypes/Point.h>

#include <vector>

namespace IRenderer {
struct Face;

using Faces = std::vector<Face>;
using Coord = MathTypes::FloatPoint3D;

struct Face
{
  unsigned int a;
  unsigned int b;
  unsigned int c;
};

struct Vertices
{
  std::vector<Coord> coords;
  std::vector<Color> colors;
};

struct Mesh
{
  Faces faces;
  Vertices vertices;
  uint32_t materialIndex;
};

static constexpr auto sizeOfCoord = sizeof(Coord);
static constexpr auto sizeOfFace = sizeof(Face);
}