#pragma once

#include <IRenderer.h>

namespace filament
{
	class Engine;
	class Scene;
}

class CFilamentRenderer : public IRenderer
{
public:
	CFilamentRenderer ( );
	~CFilamentRenderer ( );
	bool execute ( ) override;

private:
	filament::Engine* m_pEngine;
};