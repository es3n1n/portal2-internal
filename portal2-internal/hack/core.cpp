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

			std::mutex _mtx;
			std::unique_lock<std::mutex> thread_lock( _mtx );
			watcher.wait( thread_lock, [ ] ( ) -> bool { return !g::running; } );
			thread_lock.unlock( );

			// 
			// unload
			//
			util::logger::info( "Unloading, bye" );
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

		void handle_input( ) {
			if ( !util::input::get( VK_DELETE ).pressed( ) )
				return;
			g::running = false;
			watcher.notify_one( );
		}
	}
}
