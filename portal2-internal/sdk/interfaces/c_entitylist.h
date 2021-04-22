#pragma once
#include "../../util/mem/mem.h"
#include "../structs/c_base_player.h"


class c_entitylist {
public:
	c_base_entity* get_client_entity( int entity_index ) {
		// @xref: 55 8B EC 8B 55 08 83 FA FF 74 1E [client.dll]
		return util::mem::virtual_function<c_base_entity* ( __thiscall* )( void* pthis, int entity_index )>( this, 3 )( this, entity_index );
	}

	c_base_player* get_player( int entity_index ) {
		return reinterpret_cast< c_base_player* >( get_client_entity( entity_index ) );
	}
};
