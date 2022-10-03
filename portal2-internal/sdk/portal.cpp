#include "portal.h"
#include <d3d9.h>

#define DUMP(v) util::logger::debug(#v " at %p", v);

namespace portal {
    namespace modules {
        void capture() {
            TRACE_FN;

            do {
                m_client = util::mem::module_t("client.dll");
                m_engine = util::mem::module_t("engine.dll");
                m_shaderapidx9 = util::mem::module_t("shaderapidx9.dll");
                m_vguimatsurface = util::mem::module_t("vguimatsurface.dll");
                m_inputsystem = util::mem::module_t("inputsystem.dll");
            } while (!m_client || !m_engine || !m_shaderapidx9 || !m_vguimatsurface || !m_inputsystem);

            DUMP(m_client);
            DUMP(m_engine);
            DUMP(m_shaderapidx9);
            DUMP(m_vguimatsurface);
            DUMP(m_inputsystem);
        }
    } // namespace modules

    namespace patterns {
        void capture() {
            TRACE_FN;

            util::valve::crc::calc =
                modules::m_client.find_pattern("55 8B EC 51 56 8D 45 FC 50 8B F1 E8 ? ? ? ? 6A 04").cast<util::valve::crc::_get_checksum_fn>();

            DUMP(util::valve::crc::calc);

            // m_present = modules::m_gameoverlayrenderer.find_pattern( "FF 15 ? ? ? ? 8B F8 85 DB" ).offset( 2 ).self_get( 2 );
            // m_reset = modules::m_gameoverlayrenderer.find_pattern( "C7 45 ? ? ? ? ? FF 15 ? ? ? ? 8B F8" ).offset( 9 ).self_get( 2 );
        }
    } // namespace patterns

    namespace interfaces {
        void capture() {
            TRACE_FN;

            m_dx9 = modules::m_shaderapidx9.find_pattern("89 1D ? ? ? ? E8 ? ? ? ? 8B 55").offset(2).self_get(2).ptr<IDirect3DDevice9>();
            m_engine_client = modules::m_engine.capture_interface<c_engine_client>("VEngineClient015");
            m_entitylist = modules::m_client.capture_interface<c_entitylist>("VClientEntityList003");
            m_hl_client = modules::m_client.capture_interface<c_hl_client>("VClient016");
            m_input = modules::m_client.find_pattern("8B 0D ? ? ? ? 8B 01 F3 0F 10 45 ? 8B 40 0C").offset(2).self_get(2).ptr<c_input>();
            m_surface = modules::m_vguimatsurface.capture_interface<i_surface>("VGUI_Surface031");
            m_input_sys = modules::m_inputsystem.capture_interface<c_input_system>("InputSystemVersion001");
            m_input_stacksys = modules::m_inputsystem.capture_interface<c_input_stacksystem>("InputStackSystemVersion001");

            interfaces::_dump();
        }

        void _dump() {
            DUMP(m_dx9);
            DUMP(m_engine_client);
            DUMP(m_entitylist);
            DUMP(m_hl_client);
            DUMP(m_input);
            DUMP(m_surface);
            DUMP(m_input_sys);
            DUMP(m_input_stacksys);
        }
    } // namespace interfaces

    void initial() {
        TRACE_FN;

        portal::modules::capture();
        portal::patterns::capture();
        portal::interfaces::capture();
    }
} // namespace portal

#undef DUMP
