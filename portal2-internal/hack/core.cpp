#include "hack.h"

#include "hooks/hooks.h"

#include <thread>
#include <chrono>


namespace hack {
	namespace core {
		DWORD __stdcall _initial_routine( HANDLE ) {
			util::logger::startup( );

			cfg::init( );
			util::hooking::detour::init( );
			portal::initial( );
			hooks::setup( );

			_handle_unload( );

			core::_shutdown( );
			return 1; // unreachable but whatever
		}

		bool startup( ) {
			TRACE_FN;
			CreateThread( nullptr, 0, core::_initial_routine, g::dll_handle, 0, nullptr );
			return true;
		}

		void _handle_unload( ) {
			std::mutex _mtx;
			std::unique_lock<std::mutex> thread_lock( _mtx );
			watcher.wait( thread_lock, [ ] ( ) -> bool { return !g::running; } );
			thread_lock.unlock( );
		}

		void _shutdown( ) {
			TRACE_FN;
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
