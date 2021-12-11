#pragma once
#include "../hack.h"
#include <d3d9.h>

namespace hack::hooks {
	namespace hooked {
		void __stdcall create_move( int sequence_number, float input_sample_frametime, bool active );
		long __stdcall present( i_dxvk_device* device, RECT* src_rect, RECT* dest_rect, HWND dest_wnd_override, RGNDATA* dirty_region, DWORD flags );
		int __cdecl set_cursor_lock( int a1, bool is_locked );
	}

	namespace detours {
		namespace o {
			inline decltype( &hooked::set_cursor_lock ) set_cursor_lock;
			inline decltype( &hooked::present ) present;
		}

		void setup( );
		void unhook( );
	}

	namespace vmt {
		inline util::hooking::vmt m_hl_client;

		void setup( );
		void unhook( );
	}

	void setup( );
	void unhook( );
}