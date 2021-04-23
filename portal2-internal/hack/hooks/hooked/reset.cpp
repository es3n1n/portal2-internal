#include "../hooks.h"
#include "imgui_impl_dx9.h"


namespace hack::hooks::hooked {
	long __stdcall reset( IDirect3DDevice9* pthis, D3DPRESENT_PARAMETERS* params ) {
		ImGui_ImplDX9_InvalidateDeviceObjects( );
		ImGui_ImplDX9_CreateDeviceObjects( );

		return reinterpret_cast< decltype( &reset ) >( detours::o::reset )( pthis, params );
	}
}
