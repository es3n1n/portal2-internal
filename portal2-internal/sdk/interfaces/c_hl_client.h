#pragma once
#include "../misc/client_class.h"
#include "../../util/mem/mem.h"

class c_hl_client {
public:
    c_clientclass* GetAllClasses( ) {
        return util::mem::virtual_function<c_clientclass* ( __thiscall* )( void* )>( this, 8 )( this );
    };
};
