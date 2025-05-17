#pragma once

#include "FilamentTypesFwd.h"

#include <memory>
#include <vector>

namespace RendererFilament {
class CIndexBufferManager
{
public:
  void addBuffer(IndexBufferUnique);

private:
  std::vector<IndexBufferUnique> m_buffers;
};

using IndexBufferManagerShared = std::shared_ptr<CIndexBufferManager>;
}