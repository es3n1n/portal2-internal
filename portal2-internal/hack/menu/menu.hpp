#pragma once
#include "ui/imgui_custom.hpp"

namespace hack::menu {
    constexpr float_t kMenuWidth = 429.f;
    constexpr float_t kMenuHeight = 375.f;

    inline bool opened = true;

    void render();
    void toggle();
    void setup();
} // namespace hack::menu
