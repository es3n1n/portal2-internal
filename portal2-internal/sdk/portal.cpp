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
                materialsystem = util::mem::module_t("materialsystem.dll");
                studiorender = util::mem::module_t("studiorender.dll");
            } while (!server || !client || !engine || !vguimatsurface || !inputsystem || !vstdlib || !materialsystem || !studiorender);

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
            DUMP(materialsystem);
            DUMP(studiorender);
            DUMP_NOSANITY(shaderapidx9);
            DUMP_NOSANITY(shaderapivk);
            DUMP_NOSANITY(dxvk_d3d9);
        }
    } // namespace modules

    namespace sig {
        void capture() {
            TRACE_FN;

            util::game::calc_cmd_crc =
                modules::client.find_pattern("55 8B EC 51 56 8D 45 FC 50 8B F1 E8 ?? ?? ?? ?? 6A 04").cast<util::game::calc_cmd_crc_t>();

            airmove_velocity_check = modules::server.find_pattern("F3 0F 10 ?? 40 F3 0F 10 25");
            if (!airmove_velocity_check)
                airmove_velocity_check = modules::server.find_pattern("B8 ?? ?? ?? ?? FF E0 10 25"); // in case we already patched this function smh

            airmove_velocity_check_exit = modules::server.find_pattern("F3 0F 10 55 E4 F3 0F 10 ?? E8 F3 0F 58 ?? C8");

            get_clientmode = modules::client.find_pattern("E8 ?? ?? ?? ?? 83 3E 01").jmp(1);

            draw_portal = modules::client.find_pattern("55 8B EC 83 EC 14 53 8B D9 8B 0D");

            _dump();
        }

        void _dump() {
            DUMP(util::game::calc_cmd_crc);
            DUMP(airmove_velocity_check);
            DUMP(airmove_velocity_check_exit);
            DUMP(get_clientmode);
            DUMP(draw_portal);
        }
    } // namespace sig

    void _capture() {
        TRACE_FN;

        dx9 = modules::get_shaderapi().find_pattern("89 1D ?? ?? ?? ?? E8 ?? ?? ?? ?? 8B 55").offset(2).self_get(2).ptr<IDirect3DDevice9>();
        input = modules::client.find_pattern("8B 0D ?? ?? ?? ?? 8B 01 F3 0F 10 45 ?? 8B 40 0C").offset(2).self_get(2).ptr<c_input>();

        engine_client = modules::engine.capture_interface<c_engine_client>("VEngineClient015");
        entitylist = modules::client.capture_interface<c_entitylist>("VClientEntityList003");
        hl_client = modules::client.capture_interface<c_hl_client>("VClient016");
        surface = modules::vguimatsurface.capture_interface<i_surface>("VGUI_Surface031");
        input_sys = modules::inputsystem.capture_interface<c_input_system>("InputSystemVersion001");
        input_stacksys = modules::inputsystem.capture_interface<c_input_stacksystem>("InputStackSystemVersion001");
        cvar = modules::vstdlib.capture_interface<c_cvar>("VEngineCvar007");
        model_render = modules::engine.capture_interface<c_model_render>("VEngineModel016");
        material_system = modules::materialsystem.capture_interface<c_material_system>("VMaterialSystem080");
        studio_renderer = modules::studiorender.capture_interface<c_studio_renderer>("VStudioRender026");

        clientmode = sig::get_clientmode.cast<c_clientmode*(__cdecl*)()>()();

        beams = modules::client.find_pattern("89 86 ?? ?? ?? ?? 8B 0D ?? ?? ?? ?? 8B 01 8B 10").offset(8).self_get(2).ptr<i_render_beams>();

        model_info = modules::engine.capture_interface<i_model_info_client>("VModelInfoClient004");

        global_vars = modules::client.find_pattern("FF D0 8B 0D ?? ?? ?? ?? 8B 51 04 52").offset(4).self_get(2).ptr<c_global_vars>();
        prop_portal = modules::client.find_pattern("76 3A 8B 15").offset(4).self_get(2).ptr<c_prop_portal>();

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
        DUMP(clientmode);
        DUMP(model_render);
        DUMP(material_system);
        DUMP(studio_renderer);
        DUMP(beams);
        DUMP(model_info);
        DUMP(global_vars);
        DUMP(prop_portal);
    }

    void initial() {
        TRACE_FN;

        modules::capture();
        sig::capture();
        _capture();
    }

    namespace players {
        bool c_local_player::get() {
            m_idx = portal::engine_client->get_local_player();
            m_ent = portal::entitylist->get_client_entity(m_idx);
            m_pl = reinterpret_cast<c_base_player*>(m_ent);

            return valid();
        }

        c_base_player* get(int idx) {
            return reinterpret_cast<c_base_player*>(portal::entitylist->get_client_entity(idx));
        }
    } // namespace players
} // namespace portal

#undef DUMP
#undef DUMP_NOSANITY
