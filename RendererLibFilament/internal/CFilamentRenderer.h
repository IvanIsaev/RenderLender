#pragma once

#include <IRenderer.h>


class CFilamentRenderer : public IRenderer
{
public:
	bool execute ( ) override;
};