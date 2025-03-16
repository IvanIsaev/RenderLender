#pragma once

#include <string_view>


class IRenderWindow;

class IRenderArea
{
public:
	virtual ~IRenderArea ( ) = default;

	virtual void addRenderWindow ( std::string_view ) = 0;
	virtual IRenderWindow* renderWindow ( ) = 0;
};