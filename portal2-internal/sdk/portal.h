#pragma once
#include "../util/util.h"
#include "interfaces/interfaces.h"


namespace portal {
	namespace modules {
		inline util::mem::module_t m_client;
		inline util::mem::module_t m_engine;

		void capture( );
	}

	namespace patterns {
		void capture( );
	}

	namespace interfaces {
		inline c_engine_client* m_engine_client;

		void capture( );
	}

	void initial( );
}
