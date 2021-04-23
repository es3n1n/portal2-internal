#include "input.h"


namespace util::input {
	void _wndproc( const unsigned int msg, const WPARAM param ) {
		for ( auto i = 0; i < 256; i++ ) {
			if ( m_keys.at( i ).m_state != e_button_state::pressed ) continue;
			m_keys.at( i ).m_state = e_button_state::held;
		}

		switch ( msg ) {
			/// "Normal" keys
		case WM_KEYDOWN:
			if ( param >= 0 && param < 256 )
				m_keys.at( param ).m_state = e_button_state::pressed;
			break;
		case WM_KEYUP:
			if ( param >= 0 && param < 256 )
				m_keys.at( param ).m_state = e_button_state::idle;
			break;

			/// Side mouse buttons
		case WM_XBUTTONDOWN:
		case WM_XBUTTONDBLCLK:
			if ( GET_XBUTTON_WPARAM( param ) & XBUTTON1 )
				m_keys.at( VK_XBUTTON1 ).m_state = e_button_state::pressed;
			else if ( GET_XBUTTON_WPARAM( param ) & XBUTTON2 )
				m_keys.at( VK_XBUTTON2 ).m_state = e_button_state::pressed;
			break;
		case WM_XBUTTONUP:
			if ( GET_XBUTTON_WPARAM( param ) & XBUTTON1 )
				m_keys.at( VK_XBUTTON1 ).m_state = e_button_state::idle;
			else if ( GET_XBUTTON_WPARAM( param ) & XBUTTON2 )
				m_keys.at( VK_XBUTTON2 ).m_state = e_button_state::idle;
			break;

			/// System keys
		case WM_SYSKEYDOWN:
			if ( param >= 0 && param < 256 )
				m_keys.at( param ).m_state = e_button_state::pressed;
			break;
		case WM_SYSKEYUP:
			if ( param >= 0 && param < 256 )
				m_keys.at( param ).m_state = e_button_state::idle;
			break;

			/// Middle button
		case WM_MBUTTONDOWN:
		case WM_MBUTTONDBLCLK:
			m_keys.at( VK_MBUTTON ).m_state = e_button_state::pressed;
			break;
		case WM_MBUTTONUP:
			m_keys.at( VK_MBUTTON ).m_state = e_button_state::idle;
			break;

			/// Left mouse button
		case WM_LBUTTONDOWN:
		case WM_LBUTTONDBLCLK:
			m_keys.at( VK_LBUTTON ).m_state = e_button_state::pressed;
			break;
		case WM_LBUTTONUP:
			m_keys.at( VK_LBUTTON ).m_state = e_button_state::idle;
			break;

			/// Right mouse button
		case WM_RBUTTONDOWN:
		case WM_RBUTTONDBLCLK:
			m_keys.at( VK_RBUTTON ).m_state = e_button_state::pressed;
			break;
		case WM_RBUTTONUP:
			m_keys.at( VK_RBUTTON ).m_state = e_button_state::idle;
			break;
		default:
			break;
		}
	}

	key_info_t& get( const int key ) {
		return m_keys.at( key );
	}
}