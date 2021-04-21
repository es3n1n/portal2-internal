#pragma once
#include "../../util/mem/mem.h"


class c_engine_client {
public:
	int GetLocalPlayer( ) {
		return util::mem::virtual_function<int( __thiscall* )( void* )>( this, 12 )( this );
	}
};
