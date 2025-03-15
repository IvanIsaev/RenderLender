#pragma once

class IApplication
{
public:
	virtual ~IApplication ( ) = default;
	virtual bool execute ( ) = 0;
};
