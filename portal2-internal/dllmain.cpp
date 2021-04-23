#include <Windows.h>
#include "hack/hack.h"



bool __stdcall DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved ) {
	if ( fdwReason != DLL_PROCESS_ATTACH ) return TRUE;

	g::dll_handle = hinstDLL;
	g::win = FindWindowW( L"Valve001", L"PORTAL 2 - Direct3D 9" );

	return hack::core::startup( );
}
