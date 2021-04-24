#include "hack.h"

#include "hooks/hooks.h"

#include <thread>
#include <chrono>


namespace hack {
	namespace bootstrap {
		DWORD __stdcall _initial_routine( HANDLE ) {
			util::logger::startup( );

			cfg::init( );
			util::hooking::detour::init( );
			portal::initial( );
			hooks::setup( );
			util::input::init( );

			_handle_unload( );

			_shutdown( );
			return 1; // unreachable but whatever
		}

		bool startup( HANDLE dll_handle ) {
			TRACE_FN;
			_::dll_handle = dll_handle;
			CreateThread( nullptr, 0, _initial_routine, 0, 0, nullptr );
			return true;
		}

		void _handle_unload( ) {
			std::mutex _mtx;
			std::unique_lock<std::mutex> thread_lock( _mtx );
			_::watcher.wait( thread_lock, [ ] ( ) -> bool { return !running; } );
			thread_lock.unlock( );
		}

		void _shutdown( ) {
			TRACE_FN;
			hooks::unhook( );
			util::input::deinit( );
			FreeLibraryAndExitThread( static_cast< HMODULE >( _::dll_handle ), 0x1 );
		}

		void handle_input( ) {
			if ( !util::input::get( VK_DELETE ).pressed( ) )
				return;
			running = false;
			_::watcher.notify_one( );
		}
	}
}
