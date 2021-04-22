#include "detours.h"
#include "../../logger/logger.h"


#define MH_ASSERT_BEGIN std::uint32_t stat;
#define MH_ASSERT(cond, err) if ( stat = cond; cond != MH_OK ) return L_ERROR( err ": %i", stat );


namespace util::hooking::detour {
	void create( void* target, void* detour, void** orig ) {
		MH_ASSERT_BEGIN;
		MH_ASSERT( MH_CreateHook( target, detour, orig ), "Unable to create hook" );
		MH_ASSERT( MH_EnableHook( target ), "Unable to enable hook" );
	}

	void remove( void* target ) {
		MH_ASSERT_BEGIN;
		MH_ASSERT( MH_DisableHook( target ), "Unable to disable hooks" );
		MH_ASSERT( MH_RemoveHook( target ), "Unable to remove hooks" );
	}
}


#undef MH_ASSERT_BEGIN
#undef MH_ASSERT
