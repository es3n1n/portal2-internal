#pragma once
#include "util/math/math.hpp"
#include "util/mem/mem.hpp"

class i_material_var {
public:
    char* sz;
    int i;
    union {
        vec4_t vec4;
        vec3_t vec3;
    };
};

class i_material {
public:
    i_material_var* find_var(const char* var_name, bool* found_ptr, bool complain = false) {
        return util::mem::virtual_function<i_material_var*(__thiscall*)(void*, const char*, bool*, bool)>(this, 11)(this, var_name, found_ptr, complain);
    }

    void alpha_modulate(float value) {
        return util::mem::virtual_function<void(__thiscall*)(void*, float)>(this, 27)(this, value);
    }

    void color_modulate(float r, float g, float b) {
        return util::mem::virtual_function<void(__thiscall*)(void*, float, float, float)>(this, 28)(this, r, g, b);
    }
};

// CMaterialSystem
class c_material_system {
public:
    // @xref: [actual address in first opcode] E8 ? ? ? ? 85 C0 74 3F  (materialsystem.dll)
    i_material* find_material(const char* material_name, const char* group_name = nullptr, bool complain = false, const char* complain_prefix = nullptr) {
        return util::mem::virtual_function<i_material*(__thiscall*)(void*, const char*, const char*, bool, const char*)>(this, 82)(
            this, material_name, group_name, complain, complain_prefix);
    }
};
