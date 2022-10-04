#pragma once
#include "ui/imgui_custom.hpp"

namespace hack::menu {
    inline bool opened = true;

    void render();
    void toggle();
    void setup();
} // namespace hack::menu
