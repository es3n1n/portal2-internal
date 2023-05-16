#include "hooks.hpp"

namespace hack::hooks {
    namespace detours {
        void setup() { }
        void unhook() { }
    } // namespace detours

    namespace vmt {
        void setup() {
            TRACE_FN;

            hl_client.setup(portal::hl_client);
            hl_client.hook(21, hooked::create_move);

            dx9.setup(portal::dx9);
            dx9.hook(16, hooked::reset);
            dx9.hook(17, hooked::present);

            clientmode.setup(portal::clientmode);
            clientmode.hook(18, hooked::override_view);

            model_render.setup(portal::model_render);
            model_render.hook(19, hooked::draw_model_execute);
        }

        void unhook() {
            TRACE_FN;

            hl_client.unhook();
            dx9.unhook();
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