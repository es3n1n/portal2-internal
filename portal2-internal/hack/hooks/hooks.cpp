#include "hooks.h"

namespace hack::hooks {
    namespace detours {
        void setup() {
            TRACE_FN;
        }
        void unhook() {
            TRACE_FN;
        }
    } // namespace detours

    namespace vmt {
        void setup() {
            TRACE_FN;

            m_hl_client.setup(portal::interfaces::m_hl_client);
            m_dx9.setup(portal::interfaces::m_dx9);
            m_vguimatsurface.setup(portal::interfaces::m_surface);

            m_hl_client.hook(21, hooked::create_move);
            m_dx9.hook(16, hooked::reset);
            m_dx9.hook(17, hooked::present);
            //m_vguimatsurface.hook(65, hooked::lock_cursor);
        }

        void unhook() {
            TRACE_FN;

            m_hl_client.unhook();
            m_dx9.unhook();
            m_vguimatsurface.unhook();
        }
    } // namespace vmt

    void setup() {
        TRACE_FN;

        detours::setup();
        vmt::setup();
    }

    void unhook() {
        TRACE_FN;

        detours::unhook();
        vmt::unhook();
    }
} // namespace hack::hooks