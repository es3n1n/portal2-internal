#include "portal.h"


namespace portal {
	namespace modules {
		void capture() {
			client = util::mem::module_t( "client.dll" );
		}
	}

	void initial( ) {
		portal::modules::capture( );
	}
}