#pragma once

#include "mh/minhook.h"
#pragma comment(lib, "mh/minhook.lib") // warn: minhook lib might be outdated, i don't care


namespace util::hooking::detour {
	void create( void* target, void* detour, void** orig );
	void remove( void* target = nullptr /* nullptr = MH_ALL_HOOKS */ );
}
