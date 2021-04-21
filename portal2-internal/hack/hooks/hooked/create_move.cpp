#include "../hooks.h"


namespace hack::hooks::hooked {
	void __stdcall create_move( int sequence_number, float input_sample_frametime, bool active ) {
		static auto o = vmt::m_hl_client.original<void( __thiscall* )( PVOID, int, float, bool )>( 21 );
		//util::logger::debug( "createmove()" );
		TRACE_FN;
		return o( portal::interfaces::m_hl_client, sequence_number, input_sample_frametime, active );
	}
}
