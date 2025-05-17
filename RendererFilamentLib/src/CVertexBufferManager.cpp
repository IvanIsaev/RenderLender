#include "CVertexBufferManager.h"

#include <memory>

using namespace RendererFilament;

void
CVertexBufferManager::addBuffer(VertexBufferUnique vertexBuffer)
{
  m_buffers.push_back(std::move(vertexBuffer));
}
