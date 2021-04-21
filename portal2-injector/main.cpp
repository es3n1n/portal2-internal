#include <Windows.h>
#include <iostream>
#include <tlhelp32.h>
#include <stdio.h>


class Injector
{
public:
	static bool Inject( const wchar_t procName[ ], const char* dllName )
	{
		// Get the process id from the process name
		DWORD processID = GetTargetThreadIDFromProcName( procName );

		return Inject( processID, dllName );
	}

	static bool Inject( DWORD processID, const char* relativeDllName )
	{

		if ( processID == 0 )
			return false; // tlhelp was unable to find the process name

		HANDLE Proc = OpenProcess( PROCESS_ALL_ACCESS, FALSE, processID );
		if ( Proc == 0 )
		{
			// this process id clearly isnt valid or is 0 - bail!
			// this can also happen if we dont have the privileges required to access this process
			auto err = GetLastError( );
			if ( err == 5 )
				printf( "Run injector as administrator" );
			else
				printf( "OpenProcess() failed: %d", GetLastError( ) );
			return false;
		}

		static bool IsFixed { false };
		if ( !IsFixed ) {
			// fixing csgo lla
			auto LdrLoadDll = GetProcAddress( GetModuleHandleA( "ntdll.dll" ), "LdrLoadDll" );
			auto NtOpenFile = GetProcAddress( GetModuleHandleA( "ntdll.dll" ), "NtOpenFile" );

			WriteProcessMemory( Proc, LdrLoadDll, LdrLoadDll, 10, 0 );
			WriteProcessMemory( Proc, NtOpenFile, NtOpenFile, 10, 0 );
			IsFixed = true;
		}
		char DllName[ MAX_PATH ];

		// get the full path to the dll - this is important as the target processes working directory is probably different !
		GetFullPathNameA( relativeDllName, MAX_PATH, DllName, NULL );

		LPVOID LoadLib = ( LPVOID )GetProcAddress( GetModuleHandleA( "kernel32.dll" ), "LoadLibraryA" );

		// Allocate space in the process for our DLL name
		LPVOID RemoteString = VirtualAllocEx( Proc, NULL, strlen( DllName ), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE );

		// Write the string name of our DLL in the memory allocated
		WriteProcessMemory( Proc, RemoteString, DllName, strlen( DllName ), NULL );

		// Load our DLL by calling loadlibrary in the other process and passing our dll name
		CreateRemoteThread( Proc, NULL, NULL, ( LPTHREAD_START_ROUTINE )LoadLib, ( LPVOID )RemoteString, NULL, NULL );

		CloseHandle( Proc );
		return true;
	}

	static DWORD GetTargetThreadIDFromProcName( const wchar_t* ProcName )
	{
		// create a handle to the toolhelp32 library
		HANDLE thSnapShot = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
		if ( thSnapShot == INVALID_HANDLE_VALUE )
		{
			//MessageBox(NULL, "Error: Unable to create toolhelp snapshot!", "2MLoader", MB_OK);
			printf( "Error: Unable to create toolhelp snapshot!" );
			return 0;
		}

		PROCESSENTRY32 pe;
		pe.dwSize = sizeof( PROCESSENTRY32 );

		// iterate over the currently running processes to find the one whose name matches `ProcName`
		BOOL retval = Process32First( thSnapShot, &pe );
		while ( retval )
		{
			if ( !wcscmp( pe.szExeFile, ProcName ) )
			{
				// names match
				// close the handle and return the process id
				CloseHandle( thSnapShot );
				return pe.th32ProcessID;
			}
			retval = Process32Next( thSnapShot, &pe );
		}

		// unable to find the process
		// close the handle and return 0 signalling that we were unable to find the process id

		printf( "Error: unable to find the process id!\n" );

		CloseHandle( thSnapShot );

		return 0;
	}
};

int main( ) {

	if ( !Injector::Inject( L"portal2.exe", "portal2-internal.dll" ) ) {
		printf( "\n[Step 1] Failed %d.\n", GetLastError( ) );
		system( "pause" );
		//TerminateProcess(pi.hProcess, 0x0);
		goto END;
	}
END:
	return 1;
}