#include <CApplicationFactory.h>
#include <CInterfaceFactory.h>
#include <CFilamentRendererFactory.h>

int main ( int argc, char* argv [ ] )
{
	auto pApplication = CApplicationFactory::create ( argc, argv );
	auto pInterface = CInterfaceFactory::create ( );
	auto pRenderer = CFilamentRendererFactory::create ( );

	pInterface->show ( );

	pRenderer->execute ( );

	return pApplication->execute ( );
}
