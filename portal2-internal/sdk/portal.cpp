#include "portal.h"


#define DUMP_INTERFACE(v) util::logger::debug( #v " at %p", v );


namespace portal {
	namespace modules {
		void capture( ) {
			TRACE_FN;

			m_client = util::mem::module_t( "client.dll" );
			m_engine = util::mem::module_t( "engine.dll" );
		}
	}

	namespace patterns {
		void capture( ) {
			TRACE_FN;

			util::valve::crc::calc = modules::m_client.find_pattern( "55 8B EC 51 56 8D 45 FC 50 8B F1 E8 ? ? ? ? 6A 04" ).cast<util::valve::crc::_get_checksum_fn>( );

			// kinda useless 4 now, but maybe someday i will use it to store some features-related patterns
		}
	}

	namespace interfaces {
		void capture( ) {
			TRACE_FN;

			m_engine_client = modules::m_engine.capture_interface<c_engine_client>( "VEngineClient015" );
			m_entitylist = modules::m_client.capture_interface<c_entitylist>( "VClientEntityList003" );
			m_hl_client = modules::m_client.capture_interface<c_hl_client>( "VClient016" );
			m_input = modules::m_client.find_pattern( "8B 0D ? ? ? ? 8B 01 F3 0F 10 45 ? 8B 40 0C" ).offset( 2 ).self_get( 2 ).ptr<c_input>( );

			interfaces::_dump( );
		}

		void _dump( ) {
			DUMP_INTERFACE( m_engine_client );
			DUMP_INTERFACE( m_entitylist );
			DUMP_INTERFACE( m_hl_client );
			DUMP_INTERFACE( m_input );
		}
	}

	void initial( ) {
		TRACE_FN;

		portal::modules::capture( );
		portal::patterns::capture( );
		portal::interfaces::capture( );
	}
}


#undef DUMP_INTERFACE
