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
        ImGui::SetNextWindowSize(ImVec2(540, 280), ImGuiCond_Once);

        if (!ImGui::Begin("portal2 cheeto", &opened, ImGuiWindowFlags_NoCollapse))
            return ImGui::End();

        static bool first_render{true};

        ImGui::Checkbox("bhop", &opts::bhop);
        ImGui::Checkbox("autostrafer", &opts::autostrafer);
        if (ImGui::Checkbox("airacceleration_fix", &opts::airacceleration_fix) || (first_render && opts::airacceleration_fix))
            hack::features::misc::airacceleration_fix();

        constexpr float_t DEFAULT_ACCELERATION = 5.f;

        ImGui::SetNextItemWidth(150.f);
        if (ImGui::InputFloat("airacceleration", &opts::airacceleration_value, 1.f, 5.f, "%1.f") ||
            (first_render && opts::airacceleration_value != DEFAULT_ACCELERATION))
            features::misc::apply_acceleration();

        auto custom_acceleration_btn = [](const char* name, const float_t value) [[msvc::forceinline]] -> void {
            ImGui::SameLine();
            if (!ImGui::Button(name))
                return;
            features::misc::apply_acceleration(value);
        };
        custom_acceleration_btn("DEFAULT", DEFAULT_ACCELERATION);
        custom_acceleration_btn("CSGO", 12.f);
        custom_acceleration_btn("BHOP", 10000.f);

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
