#include "../hooks.h"
#include "../../features/features.h"


namespace hack::hooks::hooked {
	void __stdcall create_move( int sequence_number, float input_sample_frametime, bool active ) {
		static auto o = vmt::m_hl_client.original<void( __thiscall* )( PVOID, int, float, bool )>( 21 );

		o( portal::interfaces::m_hl_client, sequence_number, input_sample_frametime, active );

		c_usercmd* cmd = portal::interfaces::m_input->get_command( sequence_number );
		auto verified_cmd = portal::interfaces::m_input->get_verified_command( sequence_number );

		if ( !cmd || !cmd->m_number )
			return;

		int localplayer_idx = portal::interfaces::m_engine_client->get_local_player( );
		g::m_localplayer = portal::interfaces::m_entitylist->get_player( localplayer_idx );

		if ( !g::m_localplayer )
			return;

		features::create_move( cmd );

		verified_cmd->m_command = *cmd;
		verified_cmd->m_crc32 = util::valve::crc::calc( cmd );
	}
}
