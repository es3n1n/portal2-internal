#pragma once
#include "../util/util.h"
#include "../globals.h"
#include "../sdk/portal.h"
#include "cfg/cfg.h"
#include "hooks/hooks.h"
#include "menu/menu.h"
#include <condition_variable>


namespace hack::core {
	inline std::condition_variable watcher;

	DWORD __stdcall _initial_routine( HANDLE );

	bool startup( );
	void _handle_unload( );
	void _shutdown( );

	void handle_input( );
}
