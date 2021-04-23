#pragma once

#include "mh/minhook.h"
#pragma comment(lib, "util/hooking/detours/mh/minhook.lib") // warn: minhook lib might be outdated, i don't care
#include "../../mem/mem.h"


namespace util::hooking::detour {
	void init( );
	void create( mem::addr_t& target, void* detour, void** orig );
	void create( void* target, void* detour, void** orig );
	void remove( void* target = nullptr /* nullptr = MH_ALL_HOOKS */ );
}
