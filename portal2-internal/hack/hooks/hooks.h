#pragma once
#include "../hack.h"


namespace hack::hooks {
	namespace hooked {
		void __stdcall create_move( int sequence_number, float input_sample_frametime, bool active );
	}

	namespace detours {
		// @todo: add detours hooking and get rid of vmt
		void setup( );
		void unhook( );
	}

	namespace vmt {
		inline util::hooking::vmt m_hl_client;
		
		void setup( );
		void unhook( );
	}

	void setup( );
	void unhook( );
}