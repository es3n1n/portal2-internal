#include "game.hpp"
#include "hack/menu/imgui/imgui.h"
#include "sdk/portal.hpp"
#include "util/cast/cast.hpp"

namespace util::game {
    namespace {
        InputContext_t* context = nullptr;
    }

    void lock_cursor() {
        if (!context)
            context = portal::input_stacksys->push_input_context();

        portal::input_stacksys->enable_input_context(context, true);
        portal::input_stacksys->set_cursor_visible(context, false);
        portal::input_stacksys->set_mouse_capture(context, true);
    }

    void unlock_cursor() {
        int width = util::safe_cast<int>(ImGui::GetIO().DisplaySize.x / 2);
        int height = util::safe_cast<int>(ImGui::GetIO().DisplaySize.y / 2);

        if (context) {
            if (portal::input_stacksys->is_topmost_enabled_context(context))
                portal::input_stacksys->set_cursor_position(context, width, height);

            portal::input_stacksys->enable_input_context(context, false);
        }

        portal::input_sys->get_raw_mouse_accumulators(&width, &height);
    }
} // namespace util::game