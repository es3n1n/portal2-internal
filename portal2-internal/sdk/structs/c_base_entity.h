#pragma once
#include "../misc/ang_t.h"
#include "../misc/vec_t.h"


class c_base_player;


// @note: es3n1n: uploaded a netvar dump, dunno when i'll implement a netvar system :shrug:
// https://hatebin.com/laszadjpwj
#define NETVAR(t, n, off) t & n() { return *reinterpret_cast<t*>( reinterpret_cast<std::uintptr_t>(this) + off ); }


class c_base_entity {
public:
	NETVAR( vec3_t, m_vecOrigin, 0x12c );
	NETVAR( ang_t, m_angRotation, 0x120 );
	NETVAR( int, m_nModelIndex, 0x350 );
	NETVAR( int, m_fEffects, 0xe8 );
	NETVAR( int, m_iTeamNum, 0xec );
};
