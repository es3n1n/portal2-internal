#include "../hooks.h"
#include "../../../globals.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"
#include <mutex>


namespace hack::hooks::hooked {
	long __stdcall present( IDirect3DDevice9* device, RECT* src_rect, RECT* dest_rect, HWND dest_wnd_override, RGNDATA* dirty_region ) {
		static auto o = vmt::m_dx9.original<decltype( &present )>( 17 );
		static std::once_flag once_flag;

		std::call_once( once_flag, [ & ] ( ) -> void {
			ImGui::CreateContext( );
			ImGui_ImplDX9_Init( device );
			ImGui_ImplWin32_Init( g::win );
			menu::setup( );
			} );

		ImGui_ImplDX9_NewFrame( );
		ImGui_ImplWin32_NewFrame( );
		ImGui::NewFrame( );

		menu::render( );

		ImGui::EndFrame( );
		ImGui::Render( );
		ImGui_ImplDX9_RenderDrawData( ImGui::GetDrawData( ) );

		return o( device, src_rect, dest_rect, dest_wnd_override, dirty_region );
	}
}
