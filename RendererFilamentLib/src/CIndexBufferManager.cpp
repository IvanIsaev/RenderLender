#include "CIndexBufferManager.h"

#include <memory>

using namespace RendererFilament;

void
CIndexBufferManager::addBuffer(IndexBufferUnique indexBuffer)
{
  m_buffers.push_back(std::move(indexBuffer));
}
