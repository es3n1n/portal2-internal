#include "../hooks.h"
#include "imgui_impl_win32.h"


extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler( HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam );


namespace hack::hooks::hooked {
	unsigned long __stdcall wndproc( HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam ) {
		util::input::_wndproc( msg, wparam );

		menu::toggle( );

		ImGui_ImplWin32_WndProcHandler( hwnd, msg, wparam, lparam );

		if ( menu::opened && ( msg == WM_MOUSEMOVE || msg == WM_MOUSEWHEEL ) )
			return false;

		return CallWindowProcW( others::o::wndproc, hwnd, msg, wparam, lparam );
	}
}
