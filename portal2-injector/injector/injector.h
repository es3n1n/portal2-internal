#pragma once
#include <Windows.h>

// special thanks to https://github.com/emily33901/2015-load-library-injector

namespace injector {
	namespace detail {
		void* get_process_by_name( const wchar_t* name );
	}

	bool inject( const wchar_t* proc, const char* path );
	bool inject( HANDLE proc, const char* path );
}
