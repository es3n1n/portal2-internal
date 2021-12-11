#include "hooks.h"


namespace hack::hooks {
	namespace detours {
		void setup( ) {
			util::hooking::detour::create( portal::patterns::m_set_cursor_lock_fn, hooked::set_cursor_lock, reinterpret_cast< void** >( &o::set_cursor_lock ) );
			util::hooking::detour::create( portal::patterns::m_present, hooked::present, reinterpret_cast< void** >( &o::present ) );
		}
		void unhook( ) {
			util::hooking::detour::remove( );
		}
	}

	namespace vmt {
		void setup( ) {
			m_hl_client.setup( portal::interfaces::m_hl_client );

			m_hl_client.hook( 21, hooked::create_move );
		}

		void unhook( ) {
			m_hl_client.unhook( );
		}
	}

	void setup( ) {
		detours::setup( );
		vmt::setup( );
	}

	void unhook( ) {
		detours::unhook( );
		vmt::unhook( );
	}
}