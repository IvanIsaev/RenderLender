#pragma once

class IInterface
{
public:
	virtual ~IInterface ( ) = default;
	virtual void show ( ) = 0;
};
