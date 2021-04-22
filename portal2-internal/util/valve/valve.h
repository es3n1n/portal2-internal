#pragma once


namespace util::valve {
	namespace crc {
		typedef unsigned int crc32_t;

		using _get_checksum_fn = crc32_t( __thiscall* )( void* );
		inline _get_checksum_fn calc;
	}
}
