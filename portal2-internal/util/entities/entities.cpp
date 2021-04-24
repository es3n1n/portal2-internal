#include "entities.h"
#include "../../sdk/portal.h"


namespace util::entities {
	void c_local_player::get( ) {
		m_idx = portal::interfaces::m_engine_client->get_local_player( );
		m_ent = portal::interfaces::m_entitylist->get_client_entity( m_idx );
		m_pl = reinterpret_cast< c_base_player* >( m_ent );
	}

	c_base_player* get_player( int idx ) {
		return reinterpret_cast< c_base_player* >( portal::interfaces::m_entitylist->get_client_entity( idx ) );
	}
}
