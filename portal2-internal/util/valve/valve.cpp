#include "valve.h"
#include "../../hack/menu/imgui/imgui.h"
#include "../../sdk/portal.h"

namespace util::valve {
    void lock_cursor() {
        if (!context)
            context = portal::interfaces::m_input_stacksys->push_input_context();

        portal::interfaces::m_input_stacksys->enable_input_context(context, true);
        portal::interfaces::m_input_stacksys->set_cursor_visible(context, false);
        portal::interfaces::m_input_stacksys->set_mouse_capture(context, true);
    }

    void unlock_cursor() {
        int width = static_cast<int>(ImGui::GetIO().DisplaySize.x / 2);
        int height = static_cast<int>(ImGui::GetIO().DisplaySize.y / 2);

        if (context) {
            if (portal::interfaces::m_input_stacksys->is_topmost_enabled_context(context))
                portal::interfaces::m_input_stacksys->set_cursor_position(context, width, height);

            portal::interfaces::m_input_stacksys->enable_input_context(context, false);
        }

        portal::interfaces::m_input_sys->get_raw_mouse_accumulators(&width, &height);
    }
} // namespace util::valve
