#pragma once
#include "sdk/structs/c_usercmd.hpp"
#include "util/mem/mem.hpp"

struct InputContext_t {
    int m_hCursorIcon;
    bool m_bEnabled;
    bool m_bCursorVisible;
    bool m_bMouseCaptureEnabled;
};

class c_input_stacksystem {
public:
    InputContext_t* push_input_context() {
        return util::mem::virtual_function<InputContext_t*(__thiscall*)(void*)>(this, 8)(this);
    }

    void enable_input_context(InputContext_t* hContext, bool bEnable) {
        util::mem::virtual_function<void(__thiscall*)(void*, InputContext_t*, bool)>(this, 10)(this, hContext, bEnable);
    }

    void set_cursor_visible(InputContext_t* hContext, bool bEnable) {
        util::mem::virtual_function<void(__thiscall*)(void*, InputContext_t*, bool)>(this, 11)(this, hContext, bEnable);
    }

    void set_mouse_capture(InputContext_t* hContext, bool bEnable) {
        util::mem::virtual_function<void(__thiscall*)(void*, InputContext_t*, bool)>(this, 13)(this, hContext, bEnable);
    }

    void set_cursor_position(InputContext_t* hContext, int x, int y) {
        util::mem::virtual_function<void(__thiscall*)(void*, InputContext_t*, int, int)>(this, 14)(this, hContext, x, y);
    }

    bool is_topmost_enabled_context(InputContext_t* hContext) {
        return util::mem::virtual_function<bool(__thiscall*)(void*, InputContext_t*)>(this, 15)(this, hContext);
    }
};
