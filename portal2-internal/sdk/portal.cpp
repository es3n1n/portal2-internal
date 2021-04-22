#include "portal.h"


#define DUMP_INTERFACE(v) util::logger::debug( #v " at 0x%x", v );


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
		}
	}

	namespace interfaces {
		void capture( ) {
			TRACE_FN;

			m_engine_client = modules::m_engine.capture_interface<c_engine_client>( "VEngineClient015" );
			m_hl_client = modules::m_client.capture_interface<c_hl_client>( "VClient016" );
			modules::m_client.find_pattern( "55 8B EC 51 56 8D 45 FC 50 8B F1 E8 ? ? ? ? 6A 04" );
			m_input = modules::m_client.find_pattern( "8B 0D ? ? ? ? 8B 01 F3 0F 10 45 ? 8B 40 0C" ).offset( 2 ).self_get( 2 ).ptr<c_input>( );

			DUMP_INTERFACE( m_engine_client );
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
