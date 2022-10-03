#include "input.h"
#include "../../hack/hack.h"
#include "imgui_impl_win32.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

namespace util::input {
    void init() {
        auto creation_parameters = D3DDEVICE_CREATION_PARAMETERS();
        portal::interfaces::m_dx9->GetCreationParameters(&creation_parameters);
        win = creation_parameters.hFocusWindow;
        _::original = reinterpret_cast<WNDPROC>(SetWindowLongW(win, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(wndproc)));
    }

    void deinit() {
        SetWindowLongW(win, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(_::original));
    }

    unsigned long __stdcall wndproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
        for (auto i = 0; i < 256; i++) {
            if (m_keys.at(i).m_state != e_button_state::pressed)
                continue;
            m_keys.at(i).m_state = e_button_state::held;
        }

        switch (msg) {
            /// "Normal" keys
        case WM_KEYDOWN:
            if (wparam >= 0 && wparam < 256)
                m_keys.at(wparam).m_state = e_button_state::pressed;
            break;
        case WM_KEYUP:
            if (wparam >= 0 && wparam < 256)
                m_keys.at(wparam).m_state = e_button_state::idle;
            break;

            /// Side mouse buttons
        case WM_XBUTTONDOWN:
        case WM_XBUTTONDBLCLK:
            if (GET_XBUTTON_WPARAM(wparam) & XBUTTON1)
                m_keys.at(VK_XBUTTON1).m_state = e_button_state::pressed;
            else if (GET_XBUTTON_WPARAM(wparam) & XBUTTON2)
                m_keys.at(VK_XBUTTON2).m_state = e_button_state::pressed;
            break;
        case WM_XBUTTONUP:
            if (GET_XBUTTON_WPARAM(wparam) & XBUTTON1)
                m_keys.at(VK_XBUTTON1).m_state = e_button_state::idle;
            else if (GET_XBUTTON_WPARAM(wparam) & XBUTTON2)
                m_keys.at(VK_XBUTTON2).m_state = e_button_state::idle;
            break;

            /// System keys
        case WM_SYSKEYDOWN:
            if (wparam >= 0 && wparam < 256)
                m_keys.at(wparam).m_state = e_button_state::pressed;
            break;
        case WM_SYSKEYUP:
            if (wparam >= 0 && wparam < 256)
                m_keys.at(wparam).m_state = e_button_state::idle;
            break;

            /// Middle button
        case WM_MBUTTONDOWN:
        case WM_MBUTTONDBLCLK:
            m_keys.at(VK_MBUTTON).m_state = e_button_state::pressed;
            break;
        case WM_MBUTTONUP:
            m_keys.at(VK_MBUTTON).m_state = e_button_state::idle;
            break;

            /// Left mouse button
        case WM_LBUTTONDOWN:
        case WM_LBUTTONDBLCLK:
            m_keys.at(VK_LBUTTON).m_state = e_button_state::pressed;
            break;
        case WM_LBUTTONUP:
            m_keys.at(VK_LBUTTON).m_state = e_button_state::idle;
            break;

            /// Right mouse button
        case WM_RBUTTONDOWN:
        case WM_RBUTTONDBLCLK:
            m_keys.at(VK_RBUTTON).m_state = e_button_state::pressed;
            break;
        case WM_RBUTTONUP:
            m_keys.at(VK_RBUTTON).m_state = e_button_state::idle;
            break;
        default:
            break;
        }

        hack::menu::toggle();
        hack::bootstrap::handle_input();

        ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam);

        // if (hack::menu::opened && (msg == WM_MOUSEMOVE || msg == WM_MOUSEWHEEL))
        //    return true;

        return CallWindowProcW(_::original, hwnd, msg, wparam, lparam);
    }

    key_info_t& get(const int key) {
        return m_keys.at(key);
    }
} // namespace util::input