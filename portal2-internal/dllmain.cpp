#include <Windows.h>
#include "hack/hack.h"



bool __stdcall DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved ) {
	if ( fdwReason != DLL_PROCESS_ATTACH ) return TRUE;

	return hack::core::startup( );
}
