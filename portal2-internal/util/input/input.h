#pragma once
#include <Windows.h>
#include <array>


namespace util::input {
	enum class e_button_state : int {
		idle = 0,
		pressed,
		held
	};

	struct key_info_t {
		e_button_state m_state;
		
		bool pressed( ) {
			bool ret = m_state == e_button_state::pressed;
			if ( ret )
				m_state = e_button_state::held;
			return ret;
		}
		
		bool held( ) {
			return m_state == e_button_state::held;
		}
	};

	void _wndproc( const unsigned int msg, const WPARAM param );

	key_info_t& get( const int key );

	inline std::array<key_info_t, 256> m_keys;
}