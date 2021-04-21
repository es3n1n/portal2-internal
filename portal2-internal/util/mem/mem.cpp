#include "mem.h"


namespace util::mem {
	void** virtual_table( mem::addr_t inst ) {
		return inst.read<void**>( );
	}

	template< typename Fn >
	Fn virtual_function( void* inst, size_t index ) {
		return reinterpret_cast< Fn >( virtual_table( inst )[ index ] );
	}
}
