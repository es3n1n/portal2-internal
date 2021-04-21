#include "hooks.h"


namespace hack::hooks {
	namespace detours {
		void setup( ) { }
		void unhook( ) { }
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