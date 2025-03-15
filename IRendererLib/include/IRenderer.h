#pragma once

class IRenderer
{
public:
	virtual ~IRenderer ( ) = default;
	virtual bool execute ( ) = 0;
};
