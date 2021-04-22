#include "mem.h"


namespace util::mem {
	void** virtual_table( mem::addr_t inst ) {
		return inst.read<void**>( );
	}
}
