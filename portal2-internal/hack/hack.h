#pragma once
#include "../util/util.h"
#include "../sdk/portal.h"
#include "cfg/cfg.h"
#include "hooks/hooks.h"
#include "menu/menu.h"
#include <condition_variable>


namespace hack::bootstrap {
	namespace _ {
		inline std::condition_variable watcher;
		inline HANDLE dll_handle;
	}

	inline bool running = true;

	DWORD __stdcall _initial_routine( HANDLE );

	bool startup( HANDLE handle );
	void _handle_unload( );
	void _shutdown( );

	void handle_input( );
}
