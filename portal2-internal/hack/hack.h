#pragma once
#include "../util/util.h"
#include "../globals.h"


namespace hack {
	namespace core {
		DWORD __stdcall _initial_routine( );
		bool startup( );

		void _shutdown( );
	}
}
