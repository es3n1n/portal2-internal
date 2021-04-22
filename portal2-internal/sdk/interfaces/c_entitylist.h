#pragma once
#include "../../util/mem/mem.h"


class c_entitylist {
public:
	void* get_client_entity( int entity_index ) {
		// @xref: 55 8B EC 8B 55 08 83 FA FF 74 1E [client.dll]
		return util::mem::virtual_function<void* ( __thiscall* )( void* pthis, int entity_index )>( this, 3 )( this, entity_index );
	}
};
