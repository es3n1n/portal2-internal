#include "hooks.h"


namespace hack::hooks {
	namespace detours {
		void setup( ) { 
			util::hooking::detour::create( portal::patterns::m_set_cursor_lock_fn, hooked::set_cursor_lock, &o::set_cursor_lock );
		}
		void unhook( ) {
			util::hooking::detour::remove( );
		}
	}

	namespace vmt {
		void setup( ) {
			m_hl_client.setup( portal::interfaces::m_hl_client );
			m_dx9.setup( portal::interfaces::m_dx9 );

			m_hl_client.hook( 21, hooked::create_move );
			m_dx9.hook( 16, hooked::reset );
			m_dx9.hook( 17, hooked::present );
		}

		void unhook( ) {
			m_hl_client.unhook( );
			m_dx9.unhook( );
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