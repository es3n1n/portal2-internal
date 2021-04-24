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

		if ( menu::opened ) {
			if ( cmd->m_buttons & e_cmd_buttons::in_attack )
				cmd->m_buttons &= ~e_cmd_buttons::in_attack;
			if ( cmd->m_buttons & e_cmd_buttons::in_attack2 )
				cmd->m_buttons &= ~e_cmd_buttons::in_attack2;
		}

		util::entities::local.get( );
		if ( !util::entities::local.valid( ) )
			return;

		features::create_move( cmd );

		verified_cmd->m_command = *cmd;
		verified_cmd->m_crc32 = util::valve::crc::calc( cmd );
	}
}
