#include "hack.h"

#include "hooks/hooks.h"

#include <thread>
#include <chrono>


namespace hack {
	namespace core {
		DWORD __stdcall _initial_routine( HANDLE ) {
			util::logger::startup( );
			util::logger::info( "Initializing stuff" );

			cfg::init( );
			util::hooking::detour::init( );
			portal::initial( );
			hooks::setup( );

			while ( !GetAsyncKeyState( VK_DELETE ) ) // @todo: std::condition_variable + input sys based on hooked wndproc
				std::this_thread::sleep_for( std::chrono::seconds( 1 ) );

			// 
			// unload
			//
			util::logger::info( "Panic key was pressed, bye" );
			core::_shutdown( );

			return 1; // unreachable but whatever
		}

		bool startup( ) {
			CreateThread( nullptr, 0, core::_initial_routine, g::dll_handle, 0, nullptr );
			return true;
		}

		void _shutdown( ) {
			hooks::unhook( );
			FreeLibraryAndExitThread( static_cast< HMODULE >( g::dll_handle ), 0x1 );
		}
	}
}
