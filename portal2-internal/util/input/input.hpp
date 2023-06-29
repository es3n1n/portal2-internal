#pragma once
#include <array>

namespace util::input {
    enum class e_button_state : int {
        idle = 0,
        pressed,
        held
    };

    struct key_info_t {
        e_button_state m_state;

        bool pressed() {
            bool ret = m_state == e_button_state::pressed;
            if (ret)
                m_state = e_button_state::held;
            return ret;
        }

        [[nodiscard]] bool held() const {
            return m_state == e_button_state::held;
        }
    };

//    inline WNDPROC _original;
//    inline HWND win;

    void init();
    void deinit();

//    unsigned long __stdcall wndproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

    key_info_t& get(const int key);

//    inline std::array<key_info_t, 256> m_keys;
} // namespace util::input