#include "../hooks.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"
#include <mutex>


namespace hack::hooks::hooked {
	long __stdcall present( i_dxvk_device* device, RECT* src_rect, RECT* dest_rect, HWND dest_wnd_override, RGNDATA* dirty_region, DWORD flags ) {
		static std::once_flag once_flag;

		std::call_once( once_flag, [ & ] ( ) -> void {
			ImGui::CreateContext( );
			ImGui_ImplDX9_Init( device->m_d3d_device );
			ImGui_ImplWin32_Init( util::input::win );
			menu::setup( );
		} );

		ImGui_ImplDX9_NewFrame( );
		ImGui_ImplWin32_NewFrame( );
		ImGui::NewFrame( );

		menu::render( );

		ImGui::EndFrame( );
		ImGui::Render( );
		ImGui_ImplDX9_RenderDrawData( ImGui::GetDrawData( ) );

		return detours::o::present( device, src_rect, dest_rect, dest_wnd_override, dirty_region, flags );
	}
}
