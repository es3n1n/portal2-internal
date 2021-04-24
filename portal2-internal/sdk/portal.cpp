#include "portal.h"
#include <d3d9.h>
#include "../globals.h"


#define DUMP_INTERFACE(v) util::logger::debug( #v " at %p", v );


namespace portal {
	namespace modules {
		void capture( ) {
			TRACE_FN;

			m_client = util::mem::module_t( "client.dll" );
			m_engine = util::mem::module_t( "engine.dll" );
			m_shaderapidx9 = util::mem::module_t( "shaderapidx9.dll" );
			m_vguimatsurface = util::mem::module_t( "vguimatsurface.dll" );
		}
	}

	namespace patterns {
		void capture( ) {
			TRACE_FN;

			util::valve::crc::calc = modules::m_client.find_pattern( "55 8B EC 51 56 8D 45 FC 50 8B F1 E8 ? ? ? ? 6A 04" ).cast<util::valve::crc::_get_checksum_fn>( );
			m_set_cursor_lock_fn = modules::m_vguimatsurface.find_pattern( "55 8B EC 80 3D ? ? ? ? ? 8A" );

			//m_present = modules::m_gameoverlayrenderer.find_pattern( "FF 15 ? ? ? ? 8B F8 85 DB" ).offset( 2 ).self_get( 2 );
			//m_reset = modules::m_gameoverlayrenderer.find_pattern( "C7 45 ? ? ? ? ? FF 15 ? ? ? ? 8B F8" ).offset( 9 ).self_get( 2 );
		}
	}

	namespace interfaces {
		void capture( ) {
			TRACE_FN;

			/*
			.text:1002334F 53                                                              push    ebx
			.text:10023350 8B CE                                                           mov     ecx, esi
			.text:10023352 E8 99 FD FF FF                                                  call    detect_query_support
			.text:10023357 68 E1 0D 74 5E                                                  push    5E740DE1h       ; lParam
			.text:1002335C 8B CE                                                           mov     ecx, esi
			.text:1002335E 89 1D 78 A4 0D 10                                               mov     g_d3d_device, ebx ; <----------------- Here
			.text:10023364 E8 67 DD FF FF                                                  call    send_ipc_msg
			.text:10023369 8B 55 08                                                        mov     edx, [ebp+hwnd]
			.text:1002336C 8B 5D 10                                                        mov     ebx, [ebp+arg_8]
			.text:1002336F B0 FD                                                           mov     al, 0FDh ; 'ý'
			.text:10023371 20 86 A8 00 00 00                                               and     [esi+0A8h], al
			*/
			m_dx9 = modules::m_shaderapidx9.find_pattern( "89 1D ? ? ? ? E8 ? ? ? ? 8B 55 08 8B 5D 10 B0 FD 20 86 ? ? ? ? 20 46 10 8A 8E ? ? ? ?" ).offset( 2 ).self_get( 2 ).ptr< IDirect3DDevice9 >( );
			m_engine_client = modules::m_engine.capture_interface<c_engine_client>( "VEngineClient015" );
			m_entitylist = modules::m_client.capture_interface<c_entitylist>( "VClientEntityList003" );
			m_hl_client = modules::m_client.capture_interface<c_hl_client>( "VClient016" );
			m_input = modules::m_client.find_pattern( "8B 0D ? ? ? ? 8B 01 F3 0F 10 45 ? 8B 40 0C" ).offset( 2 ).self_get( 2 ).ptr<c_input>( );
			m_surface = modules::m_vguimatsurface.capture_interface<i_surface>( "VGUI_Surface031" );

			interfaces::_dump( );
		}

		void _dump( ) {
			DUMP_INTERFACE( m_dx9 );
			DUMP_INTERFACE( m_engine_client );
			DUMP_INTERFACE( m_entitylist );
			DUMP_INTERFACE( m_hl_client );
			DUMP_INTERFACE( m_input );
			DUMP_INTERFACE( m_surface );
		}
	}

	void initial( ) {
		TRACE_FN;

		portal::modules::capture( );
		portal::patterns::capture( );
		portal::interfaces::capture( );

		auto creation_parameters = D3DDEVICE_CREATION_PARAMETERS( );
		interfaces::m_dx9->GetCreationParameters( &creation_parameters );
		g::win = creation_parameters.hFocusWindow;
	}
}


#undef DUMP_INTERFACE
