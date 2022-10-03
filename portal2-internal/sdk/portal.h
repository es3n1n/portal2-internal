#pragma once
#include "../util/util.h"
#include "enums/enums.h"
#include "interfaces/interfaces.h"
#include <d3d9.h>

namespace portal {
    inline bool is_vulkan_enabled = false;

    namespace modules {
        inline util::mem::module_t m_client;
        inline util::mem::module_t m_engine;
        inline util::mem::module_t m_vguimatsurface;
        inline util::mem::module_t m_inputsystem;

        // @note: @es3n1n: d3d9 stuff
        //
        inline util::mem::module_t m_shaderapidx9;

        // @note: @es3n1n: vulkan stuff
        //
        inline util::mem::module_t m_shaderapivk;
        inline util::mem::module_t m_dxvk_d3d9;

        void capture();

        __forceinline util::mem::module_t get_shaderapi() {
            return is_vulkan_enabled ? m_shaderapivk : m_shaderapidx9;
        }
    } // namespace modules

    namespace patterns {
        void capture();
    }

    namespace interfaces {
        inline IDirect3DDevice9* m_dx9;
        inline c_engine_client* m_engine_client;
        inline c_entitylist* m_entitylist;
        inline c_hl_client* m_hl_client;
        inline c_input* m_input;
        inline i_surface* m_surface;
        inline c_input_system* m_input_sys;
        inline c_input_stacksystem* m_input_stacksys;

        void capture();
        void _dump();
    } // namespace interfaces

    void initial();
} // namespace portal
