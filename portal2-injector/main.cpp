#include "injector/injector.h"


int main( ) {
	if ( !injector::inject( L"portal2.exe", "portal2-internal.dll" ) )
		system( "pause" );

	return EXIT_SUCCESS;
}
