#pragma once
#include "../hack.h"
#include <d3d9.h>

namespace hack::hooks {
	namespace hooked {
		void __stdcall create_move( int sequence_number, float input_sample_frametime, bool active );
		long __stdcall present( IDirect3DDevice9* device, RECT* src_rect, RECT* dest_rect, HWND dest_wnd_override, RGNDATA* dirty_region );
		long __stdcall reset( IDirect3DDevice9* pthis, D3DPRESENT_PARAMETERS* params );
		int __cdecl set_cursor_lock( int a1, bool is_locked );
	}

	namespace detours {
		namespace o { 
			inline void* set_cursor_lock;
		}

		void setup( );
		void unhook( );
	}

	namespace vmt {
		inline util::hooking::vmt m_hl_client;
		inline util::hooking::vmt m_dx9;
		
		void setup( );
		void unhook( );
	}

	void setup( );
	void unhook( );
}