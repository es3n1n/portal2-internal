#include "hooks.h"


namespace hack::hooks {
	namespace detours {
		void setup( ) {
			util::hooking::detour::create( portal::patterns::m_present, hooked::present, &o::present );
			util::hooking::detour::create( portal::patterns::m_reset, hooked::reset, &o::reset );
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

	namespace others {
		void setup( ) {
			o::wndproc = reinterpret_cast< WNDPROC >( SetWindowLongW( g::win, GWLP_WNDPROC, reinterpret_cast< LONG_PTR >( hooked::wndproc ) ) );
		}

		void unhook( ) {
			SetWindowLongW( g::win, GWLP_WNDPROC, reinterpret_cast< LONG_PTR >( o::wndproc ) );
		}
	}

	void setup( ) {
		detours::setup( );
		vmt::setup( );
		others::setup( );
	}

	void unhook( ) {
		detours::unhook( );
		vmt::unhook( );
		others::unhook( );
	}
}