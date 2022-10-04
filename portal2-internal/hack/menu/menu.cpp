#include "menu.hpp"
#include "hack/cfg/cfg.hpp"
#include "hack/hack.hpp"
#include "util/util.hpp"
#include <Windows.h>

namespace hack::menu {
    void render() {
        if (!opened)
            return;

        ImGui::SetNextWindowPos(ImGui::GetIO().DisplaySize * 0.5f, ImGuiCond_Once, ImVec2(0.5f, 0.5f));
        ImGui::SetNextWindowSize(ImVec2(500, 450), ImGuiCond_Once);

        if (!ImGui::Begin("portal2 cheeto", &opened, ImGuiWindowFlags_NoCollapse))
            return ImGui::End();

        static bool first_render{true};

        ImGui::Checkbox("bhop", &opts::bhop);
        ImGui::Checkbox("autostrafer", &opts::autostrafer);
        if (ImGui::Checkbox("airacceleration_fix", &opts::airacceleration_fix) || (first_render && opts::airacceleration_fix))
            hack::features::misc::airacceleration_fix();
        if (ImGui::Checkbox("csgolike_air_speed", &opts::csgolike_air_speed) || (first_render && opts::csgolike_air_speed))
            hack::features::misc::csgolike_air_speed();

        ImGui::Spacing();

        if (ImGui::Button("save"))
            cfg::save("config");
        ImGui::SameLine();
        if (ImGui::Button("load"))
            cfg::read("config");

        ImGui::End();
        first_render = false;
    }

    void toggle() {
        if (!util::input::get(VK_INSERT).pressed())
            return;

        opened ^= true;

        if (opened)
            util::valve::lock_cursor();
        else
            util::valve::unlock_cursor();
    }

    void setup() {
        auto& io = ImGui::GetIO();
        io.LogFilename = NULL;
        io.IniFilename = NULL;
    }
} // namespace hack::menu
