#pragma once
#include "ui/imgui_custom.hpp"

namespace hack::menu {
    constexpr float kMenuWidth = 429.f;
    constexpr float kMenuHeight = 450.f;

    inline bool opened = true;

    void render();
    void toggle();
    void setup();
} // namespace hack::menu
