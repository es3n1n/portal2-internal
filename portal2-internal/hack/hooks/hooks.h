#pragma once
#include "../hack.h"
#include <d3d9.h>

// @todo: find out analog of i_surface::lock_cursor, because in this game it's implemented like this lmao: https://imgur.com/a/kHffIeO
namespace hack::hooks {
	namespace hooked {
		void __stdcall create_move( int sequence_number, float input_sample_frametime, bool active );
		long __stdcall present( IDirect3DDevice9* device, RECT* src_rect, RECT* dest_rect, HWND dest_wnd_override, RGNDATA* dirty_region );
		long __stdcall reset( IDirect3DDevice9* pthis, D3DPRESENT_PARAMETERS* params );
		unsigned long __stdcall wndproc( HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam );
	}

	namespace detours {
		namespace o { }

		void setup( );
		void unhook( );
	}

	namespace vmt {
		inline util::hooking::vmt m_hl_client;
		inline util::hooking::vmt m_dx9;
		
		void setup( );
		void unhook( );
	}

	namespace others {
		namespace o {
			inline WNDPROC wndproc;
		}

		void setup( );
		void unhook( );
	}

	void setup( );
	void unhook( );
}