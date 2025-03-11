#pragma once

#include <IRenderer.h>

#include "rendererlib_export.h"

#include <memory>


class RENDERERLIB_EXPORT CFilamentRendererFactory
{
public:
	static std::unique_ptr<IRenderer> create ( );
};
