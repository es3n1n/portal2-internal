#include "hack.h"
#include <thread>
#include <chrono>


namespace hack {
	namespace core {
		void _initial_routine( ) {
			util::logger::startup( );
			util::logger::info( "Initializing stuff" );


			while ( !GetAsyncKeyState( VK_DELETE ) ) // @todo: std::condition_variable + input sys based on hooked wndproc
				std::this_thread::sleep_for( std::chrono::seconds( 1 ) );


			// 
			// unload
			//
			util::logger::info( "Panic key was pressed, bye" );
			core::_shutdown( );
		}

		bool startup( ) {
			std::thread( [ ] ( ) -> void {
				core::_initial_routine( );
				} ).detach( );
				return true;
		}

		void _shutdown( ) {

		}
	}
}
