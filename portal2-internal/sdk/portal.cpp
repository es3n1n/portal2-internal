#include "portal.hpp"
#include <d3d9.h>

#define DUMP_NOSANITY(v) util::logger::debug(#v " at %p", v);
#ifndef _DEBUG
    #define DUMP(v) DUMP_NOSANITY(v)
#else
    #define DUMP(v)         \
        DUMP_NOSANITY(v);   \
        if (!v) {           \
            __debugbreak(); \
        }
#endif

namespace portal {
    namespace modules {
        void capture() {
            TRACE_FN;

            // @note: @es3n1n: wait for game modules and capture them
            //
            do {
                server = util::mem::module_t("server.dll");
                client = util::mem::module_t("client.dll");
                engine = util::mem::module_t("engine.dll");
                vguimatsurface = util::mem::module_t("vguimatsurface.dll");
                inputsystem = util::mem::module_t("inputsystem.dll");
                vstdlib = util::mem::module_t("vstdlib.dll");
            } while (!server || !client || !engine || !vguimatsurface || !inputsystem || !vstdlib);

            // @note: @es3n1n: d3d9 stuff
            //
            shaderapidx9 = util::mem::module_t("shaderapidx9.dll");

            // @note: @es3n1n: vulkan stuff
            //
            shaderapivk = util::mem::module_t("shaderapivk.dll");
            dxvk_d3d9 = util::mem::module_t("dxvk_d3d9.dll");

            // @note: @es3n1n: detect if we're on `-vulkan` game ver
            //
            is_vulkan_enabled = static_cast<bool>(dxvk_d3d9);

            _dump();
        }

        void _dump() {
            DUMP(server);
            DUMP(client);
            DUMP(engine);
            DUMP(vguimatsurface);
            DUMP(inputsystem);
            DUMP(vstdlib);
            DUMP_NOSANITY(shaderapidx9);
            DUMP_NOSANITY(shaderapivk);
            DUMP_NOSANITY(dxvk_d3d9);
        }
    } // namespace modules

    namespace patterns {
        void capture() {
            TRACE_FN;

            util::valve::calc_cmd_crc =
                modules::client.find_pattern("55 8B EC 51 56 8D 45 FC 50 8B F1 E8 ? ? ? ? 6A 04").cast<util::valve::calc_cmd_crc_t>();
            airmove_velocity_check = modules::server.find_pattern("F3 0F 10 58 ? F3 0F 10 25");

            // m_present = modules::m_gameoverlayrenderer.find_pattern( "FF 15 ? ? ? ? 8B F8 85 DB" ).offset( 2 ).self_get( 2 );
            // m_reset = modules::m_gameoverlayrenderer.find_pattern( "C7 45 ? ? ? ? ? FF 15 ? ? ? ? 8B F8" ).offset( 9 ).self_get( 2 );
        }

        void _dump() {
            DUMP(util::valve::calc_cmd_crc);
            DUMP(airmove_velocity_check);
        }
    } // namespace patterns

    void _capture() {
        TRACE_FN;

        dx9 = modules::get_shaderapi().find_pattern("89 1D ? ? ? ? E8 ? ? ? ? 8B 55").offset(2).self_get(2).ptr<IDirect3DDevice9>();
        engine_client = modules::engine.capture_interface<c_engine_client>("VEngineClient015");
        entitylist = modules::client.capture_interface<c_entitylist>("VClientEntityList003");
        hl_client = modules::client.capture_interface<c_hl_client>("VClient016");
        input = modules::client.find_pattern("8B 0D ? ? ? ? 8B 01 F3 0F 10 45 ? 8B 40 0C").offset(2).self_get(2).ptr<c_input>();
        surface = modules::vguimatsurface.capture_interface<i_surface>("VGUI_Surface031");
        input_sys = modules::inputsystem.capture_interface<c_input_system>("InputSystemVersion001");
        input_stacksys = modules::inputsystem.capture_interface<c_input_stacksystem>("InputStackSystemVersion001");
        cvar = modules::vstdlib.capture_interface<c_cvar>("VEngineCvar007");

        _dump();
    }

    void _dump() {
        DUMP(dx9);
        DUMP(engine_client);
        DUMP(entitylist);
        DUMP(hl_client);
        DUMP(input);
        DUMP(surface);
        DUMP(input_sys);
        DUMP(input_stacksys);
        DUMP(cvar);
    }

    void initial() {
        TRACE_FN;

        portal::modules::capture();
        portal::patterns::capture();
        portal::_capture();
    }
} // namespace portal

#undef DUMP
