#include <CApplicationFactory.h>
#include <CInterfaceFactory.h>


int main ( int argc, char* argv [ ] )
{
	auto pApplication = CApplicationFactory::create ( argc, argv );
	auto pInterface = CInterfaceFactory::create ( );

	pInterface->show ( );

	return pApplication->execute ( );
}
