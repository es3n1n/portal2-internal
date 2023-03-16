#pragma once
#include "enums/enums.hpp"
#include "interfaces/interfaces.hpp"
#include "misc/color_t.hpp"
#include "util/util.hpp"
#include <d3d9.h>

namespace portal {
    inline bool is_vulkan_enabled = false;

    namespace modules {
        inline util::mem::module_t server;
        inline util::mem::module_t client;
        inline util::mem::module_t engine;
        inline util::mem::module_t vguimatsurface;
        inline util::mem::module_t inputsystem;
        inline util::mem::module_t vstdlib;
        inline util::mem::module_t materialsystem;
        inline util::mem::module_t studiorender;

        // @note: @es3n1n: d3d9 stuff
        //
        inline util::mem::module_t shaderapidx9;

        // @note: @es3n1n: vulkan stuff
        //
        inline util::mem::module_t shaderapivk;
        inline util::mem::module_t dxvk_d3d9;

        void capture();
        void _dump();

        __forceinline util::mem::module_t get_shaderapi() {
            return is_vulkan_enabled ? shaderapivk : shaderapidx9;
        }
    } // namespace modules

    namespace sig {
        // @note: @es3n1n: CPortalGameMovement::AirMove
        inline util::mem::addr_t airmove_velocity_check;
        inline util::mem::addr_t airmove_velocity_check_exit;
        inline util::mem::addr_t get_clientmode; // GetClientMode

        void capture();
        void _dump();
    } // namespace sig

    inline IDirect3DDevice9* dx9;
    inline c_engine_client* engine_client;
    inline c_entitylist* entitylist;
    inline c_hl_client* hl_client;
    inline c_input* input;
    inline i_surface* surface;
    inline c_input_system* input_sys;
    inline c_input_stacksystem* input_stacksys;
    inline c_cvar* cvar;
    inline c_clientmode* clientmode;
    inline c_model_render* model_render;
    inline c_material_system* material_system;
    inline c_studio_renderer* studio_renderer;

    void _capture();
    void _dump();

    void initial();

    namespace players {
        c_base_player* get(int idx);

        inline class c_local_player {
        private:
            c_base_entity* m_ent;
            c_base_player* m_pl;
            int m_idx;
        public:
            c_base_player* operator->() {
                return m_pl;
            }
            c_base_entity* ent() {
                return m_ent;
            }
            int idx() {
                return m_idx;
            }
            bool valid() {
                return static_cast<bool>(m_pl);
            }
            bool get();
        } local;
    } // namespace players
} // namespace portal
