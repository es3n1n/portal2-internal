#pragma once
#include "../addr/addr.h"
#include "../../logger/logger.h"
#include <string>
#include <Windows.h>
#include <vector>


namespace util::mem {
	struct module_t {
	public:
		//
		// constructors, etc...
		module_t( ) : m_name( "none" ), m_addr( ) {};
		module_t( const char* module_name ) : m_name( module_name ), m_addr( GetModuleHandleA( module_name ) ) {};
		~module_t( ) = default;

	public:
		mem::addr_t find_pattern( std::string_view pattern ) {
			auto sizeOfImage = get_nt_headers( )->OptionalHeader.SizeOfImage;

			auto pattern_bytes = pattern_to_byte( pattern );
			auto pattern_data = pattern_bytes.data( );

			for ( DWORD i = 0ul; i < sizeOfImage - pattern_bytes.size( ); i++ ) {
				bool found = true;

				for ( size_t j = 0ul; j < pattern_bytes.size( ); ++j ) {
					if ( m_addr.offset( i + j ).read<std::uint32_t>( ) == pattern_data[ j ] || pattern_data[ j ] != -1 )
						continue;

					found = false;
					break;
				}

				if ( !found )
					continue;

				auto ret = m_addr.offset( i );
				util::logger::debug( "Found '%s' sig from %s at 0x%x", pattern.data( ), m_name, static_cast< std::uintptr_t >( ret ) );
				return ret;
			}

			util::logger::error( "Signature from %s '%s' not found", m_name, pattern.data( ) );
			return mem::addr_t( );
		}
	protected:
		IMAGE_DOS_HEADER* get_dos_headers( ) {
			return m_addr.ptr<IMAGE_DOS_HEADER>( );
		}

		IMAGE_NT_HEADERS* get_nt_headers( ) {
			return m_addr.offset( get_dos_headers( )->e_lfanew ).ptr< IMAGE_NT_HEADERS >( );
		}
	protected:
		std::vector< std::uint32_t > pattern_to_byte( std::string_view pattern ) {
			auto bytes = std::vector<std::uint32_t> {};
			auto start = const_cast< char* >( pattern.data( ) );
			auto len = pattern.length( );
			auto end = const_cast< char* >( start ) + len;
			bytes.reserve( len / 3 + 5 );

			for ( auto current = start; current < end; ++current ) {
				if ( *current == '?' ) {
					++current;

					if ( *current == '?' )
						++current;

					bytes.emplace_back( -1 );
				}
				else
					bytes.emplace_back( strtoul( current, &current, 16 ) );
			}
			return bytes;
		}

	private:
		const char* m_name;
		mem::addr_t m_addr;
	};
}