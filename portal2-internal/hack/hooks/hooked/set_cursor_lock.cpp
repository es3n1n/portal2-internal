#include "../hooks.h"


namespace hack::hooks::hooked {
	int __cdecl set_cursor_lock( int a1, bool is_locked ) {
		if ( menu::opened )
			is_locked = false;
		return reinterpret_cast< decltype( &set_cursor_lock ) >( detours::o::set_cursor_lock )( a1, is_locked );
	}
}
