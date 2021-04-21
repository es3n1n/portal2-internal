#pragma once
#include "../util/mem/mem.h"


namespace portal {
	namespace modules {
		inline util::mem::module_t client /*= util::mem::module_t( "client.dll" )*/;

		void capture( );
	}

	void initial( );
}
