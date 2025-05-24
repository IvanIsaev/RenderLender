#pragma once

#include "FilamentTypesFwd.h"

#include <memory>
#include <vector>

namespace RendererFilament {
class CVertexBufferManager
{
public:
  void addBuffer(VertexBufferUnique);

private:
  std::vector<VertexBufferUnique> m_buffers;
};

using VertexBufferManagerShared = std::shared_ptr<CVertexBufferManager>;
}