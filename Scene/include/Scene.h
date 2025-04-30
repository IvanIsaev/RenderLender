#pragma once

#include "SceneTypesFwd.h"

#include <memory>
#include <string>
#include <vector>

struct Node
{
  std::vector<Node*> children;
  std::vector<unsigned int> meshesIds;
  FloatMatrix4x4 transformation;
  std::string name;
};

struct Face
{
  std::vector<unsigned int> verticesId;
};

struct Mesh
{
  std::vector<Face> faces;
  std::vector<FloatPointXYZ> vertices;
};

struct Scene
{
  Node* root = nullptr;
  std::vector<std::unique_ptr<Node>> nodes;
  std::vector<Mesh> meshes;
};

using SceneUnique = std::unique_ptr<Scene>;
