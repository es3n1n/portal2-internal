#pragma once
#include "../util/util.h"
#include "../globals.h"
#include "../sdk/portal.h"
#include "cfg/cfg.h"
#include "hooks/hooks.h"
#include "menu/menu.h"


namespace hack::core {
	DWORD __stdcall _initial_routine( HANDLE );
	bool startup( );

	void _shutdown( );
}
