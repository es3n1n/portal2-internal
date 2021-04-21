#pragma once
#include "../util/util.h"
#include "../globals.h"
#include "../sdk/portal.h"


namespace hack {
	namespace core {
		DWORD __stdcall _initial_routine( HANDLE );
		bool startup( );

		void _shutdown( );
	}
}
