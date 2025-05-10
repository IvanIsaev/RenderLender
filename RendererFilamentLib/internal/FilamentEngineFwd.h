#pragma once

#include <memory>

namespace filament {
class Engine;
}

namespace RendererFilament {
using EngineShared = std::shared_ptr<filament::Engine>;
}