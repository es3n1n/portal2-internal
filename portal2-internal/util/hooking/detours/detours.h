#pragma once

#include "mh/minhook.h"
#pragma comment(lib, "mh/minhook.lib")


namespace util::hooking::detour {
	void create( void* target, void* detour, void** orig );
	void remove( void* target = nullptr /* nullptr = MH_ALL_HOOKS */ );
}
