#pragma once
#include <cstdint>
#include <stdio.h>
#include <Windows.h>
#include <functional>

#ifdef _DEBUG
#define LOG_DEBUG_MESSAGES
#define ALLOC_CONSOLE
#endif

#define L_ERROR(...) util::logger::error(__FUNCTION__ "(): " __VA_ARGS__);
#define TRACE_FN util::logger::debug( "%s()", __FUNCTION__ );

#define CREATE_LOGGER_METHOD(n) inline void n(const char* fmt, ...) { char buf[1024]; va_list va; va_start( va, fmt ); _vsnprintf_s( buf, 1024, fmt, va ); va_end( va ); log( #n, e_level_color::level_color_ ##n, buf ); }


namespace util {
	namespace logger {
		enum class e_level_color : uint32_t {
			level_color_none = 15, // black bg and white fg
			level_color_debug = 8,
			level_color_info = 10,
			level_color_warn = 14,
			level_color_error = 12
		};

		namespace _colors {
			extern void* m_console_handle;

			bool ensure_handle( );
			void apply( uint32_t clr );
			void reset( );
			void colorify( uint32_t clr, std::function<void( )> cb );
		}

		void log( const char* prefix, e_level_color level, const char* message );

#ifdef LOG_DEBUG_MESSAGES
		CREATE_LOGGER_METHOD( debug );
#else
		inline void debug( const char* fmt, ... ) { }
#endif

		CREATE_LOGGER_METHOD( info );
		CREATE_LOGGER_METHOD( warn );
		CREATE_LOGGER_METHOD( error );

		void startup( );
	}
}

#undef CREATE_LOGGER_METHOD
