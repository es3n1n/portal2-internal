#include "injector.h"
#include <TlHelp32.h>
#include <stdio.h>


#define INJECTOR_FAIL(s) { printf(s " Error code: %d\n", GetLastError( ) ); if ( proc ) CloseHandle(proc); return false; }


namespace injector {
	namespace detail {
		void* get_process_by_name( const wchar_t* name ) {
			void* thSnapShot = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
			if ( thSnapShot == INVALID_HANDLE_VALUE )
				return nullptr;

			PROCESSENTRY32W pe;
			pe.dwSize = sizeof( PROCESSENTRY32W );

			unsigned long ret = 0;
			for ( bool proc = Process32FirstW( thSnapShot, &pe ); proc; proc = Process32NextW( thSnapShot, &pe ) ) {
				if ( wcscmp( pe.szExeFile, name ) )
					continue;
				ret = pe.th32ProcessID;
				break;
			}

			CloseHandle( thSnapShot );

			return ret ? OpenProcess( PROCESS_ALL_ACCESS, false, ret ) : nullptr;
		}
	}

	bool inject( const wchar_t* proc, const char* path ) {
		return ::injector::inject( detail::get_process_by_name( proc ), path );
	}

	bool inject( HANDLE proc, const char* path ) {
		if ( !proc )
			INJECTOR_FAIL( "Failed to open a process. Make sure injector is running as an admin." );

		char full_path[ 260 ];
		if ( !GetFullPathNameA( path, sizeof( full_path ), full_path, nullptr ) )
			INJECTOR_FAIL( "Failed to find a dll." );

		HMODULE kernel32 = GetModuleHandleW( L"kernel32.dll" );
		if ( !kernel32 )
			INJECTOR_FAIL( "Failed to get kernel32.dll handle." );

		void* lla = reinterpret_cast< void* >( GetProcAddress( kernel32, "LoadLibraryA" ) );
		if ( !lla )
			INJECTOR_FAIL( "Failed to find LoadLibraryA function." );

		void* str = VirtualAllocEx( proc, nullptr, strlen( full_path ), MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE );
		if ( !str )
			INJECTOR_FAIL( "Failed to allocate memory region for str." );

		WriteProcessMemory( proc, str, full_path, strlen( full_path ), nullptr );
		CreateRemoteThread( proc, nullptr, 0, reinterpret_cast< LPTHREAD_START_ROUTINE >( lla ), str, 0, nullptr );

		CloseHandle( proc );
		return true;
	}
}


#undef INJECTOR_FAIL
