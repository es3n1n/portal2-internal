#include "../hooks.h"


namespace hack::hooks::hooked {
	void __stdcall create_move( int sequence_number, float input_sample_frametime, bool active ) {
		static auto o = vmt::m_hl_client.original<void( __thiscall* )( PVOID, int, float, bool )>( 21 );

		o( portal::interfaces::m_hl_client, sequence_number, input_sample_frametime, active );

		int localplayer_idx = portal::interfaces::m_engine_client->get_local_player( );
		void* localplayer = portal::interfaces::m_entitylist->get_client_entity( localplayer_idx );
		util::logger::debug( "localplayer: [idx: %i ent: 0x%x]", localplayer_idx, localplayer );
		if ( localplayer ) {
			auto cmd = portal::interfaces::m_input->get_command( sequence_number );
			if ( !cmd )
				util::logger::debug( "cmd = nullptr" );
			else if ( cmd->m_buttons & e_cmd_buttons::in_jump )
				util::logger::debug( "jumping" );
		}
	}
}
