#pragma once

#include <IRenderer.h>


class CFilamentRenderer : public IRenderer
{
public:
	CFilamentRenderer ( );
	bool execute ( ) override;
};