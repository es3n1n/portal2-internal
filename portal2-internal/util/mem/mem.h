#pragma once
#include "addr/addr.h"
#include "module/module.h"


namespace util::mem {
	void** virtual_table( mem::addr_t inst );

	template< typename Fn >
	Fn virtual_function( void* inst, size_t index );
}
