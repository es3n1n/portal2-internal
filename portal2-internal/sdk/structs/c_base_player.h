#pragma once
#include "c_base_entity.h"
#include <cstdint>


class c_base_player : public c_base_entity {
public:
	int get_flags( ) {
		return *reinterpret_cast< int* >( reinterpret_cast< std::uintptr_t >( this ) + 0xF8 );
	}
};
