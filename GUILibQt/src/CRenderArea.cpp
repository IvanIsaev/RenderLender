#include <CRenderArea.h>

#include <CRenderWindow.h>


void CRenderArea::addRenderWindow ( std::string_view title )
{
	auto pRenderWindow = new CRenderWindow;
	addTab ( pRenderWindow, QString(title.data()) );
}

IRenderWindow* CRenderArea::renderWindow ( )
{
	return nullptr;
}
