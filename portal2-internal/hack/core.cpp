#include "hack.h"
#include <thread>


namespace hack {
	namespace core {
		void _initial_routine( ) {
			util::logger::startup( );
			util::logger::info( "Initializing stuff" );
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
