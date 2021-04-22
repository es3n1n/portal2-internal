#pragma once
#include "../../util/mem/mem.h"
#include "../structs/c_usercmd.h"


#define MULTIPLAYER_BACKUP 150


class c_input {
public:
	c_usercmd* get_command( int sequence_num ) {
		// @xref: 55 8B EC 83 EC 60 0F 57 C0 33 C0 56  [client.dll]
		return util::mem::virtual_function<c_usercmd* ( __thiscall* )( void* pthis, int slot, int sequence_number )>( this, 8 )( this, 0, sequence_num );
	}

	c_verified_usercmd* get_verified_command( int sequence_number ) { // tyty csgosimple
		auto verifiedCommands = *( c_verified_usercmd** )( reinterpret_cast< uint32_t >( this ) + 0xF8 );
		return &verifiedCommands[ sequence_number % MULTIPLAYER_BACKUP ];
	}
};
