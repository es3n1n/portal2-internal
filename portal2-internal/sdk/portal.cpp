#include "portal.h"


namespace portal {
	namespace modules {
		void capture() {
			client = util::mem::module_t( "client.dll" );

			auto sig = client.find_pattern( "55 8B EC 51 56 8D 45 FC 50 8B F1 E8 ? ? ? ? 6A 04" );
		}
	}

	void initial( ) {
		portal::modules::capture( );
	}
}