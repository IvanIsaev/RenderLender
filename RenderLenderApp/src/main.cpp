#include <CApplicationFactory.h>
#include <CInterfaceFactory.h>
#include <CFilamentRendererFactory.h>

#include <IRenderArea.h>

int main ( int argc, char* argv [ ] )
{
	auto pApplication = CApplicationFactory::create ( argc, argv );
	auto pInterface = CInterfaceFactory::create ( );
	auto pRenderer = CFilamentRendererFactory::create ( );

	pInterface->init ( );
	pInterface->show ( );
	auto pRenderArea = pInterface->renderArea ( );
	pRenderArea->addRenderWindow ( "Bla" );

	pRenderer->execute ( );

	return pApplication->execute ( );
}
