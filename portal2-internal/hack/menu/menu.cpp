#include "menu.hpp"
#include "hack/cfg/cfg.hpp"
#include "hack/hack.hpp"
#include "util/util.hpp"
#include <Windows.h>

namespace hack::menu {
    constexpr float_t kDefaultAirAccelerationValue = 5.f;
    constexpr float_t kCSGOAirAccelerationValue = 12.f;
    constexpr float_t kBhopAirAccelerationValue = 10000.f;

    void render() {
        if (!opened)
            return;

        ImGui::SetNextWindowPos(ImGui::GetIO().DisplaySize * 0.5f, ImGuiCond_Once, ImVec2(0.5f, 0.5f));
        ImGui::SetNextWindowSize(ImVec2(kMenuWidth, kMenuHeight), ImGuiCond_Once);

        if (!ImGui::Begin("portal2 cheeto", &opened, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize))
            return ImGui::End();

        static bool first_render{true};

        ImGui::Checkbox("bhop", &opts::bhop);
        ImGui::Checkbox("autostrafer", &opts::autostrafer);
        if (ImGui::Checkbox("airacceleration_fix", &opts::airacceleration_fix) || (first_render && opts::airacceleration_fix))
            hack::features::misc::airacceleration_fix();

        ImGui::SetNextItemWidth(150.f);
        if (ImGui::InputFloat("airacceleration", &opts::airacceleration_value, 1.f, 5.f, "%1.f") ||
            (first_render && opts::airacceleration_value != kDefaultAirAccelerationValue))
            features::misc::apply_acceleration();

        auto custom_acceleration_btn = [](const char* name, const float_t value) [[msvc::forceinline]] -> void {
            ImGui::SameLine();
            if (!ImGui::Button(name))
                return;
            features::misc::apply_acceleration(value);
        };

        custom_acceleration_btn("DEFAULT", kDefaultAirAccelerationValue);
        custom_acceleration_btn("CSGO", kCSGOAirAccelerationValue);
        custom_acceleration_btn("BHOP", kBhopAirAccelerationValue);

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
        return opened ? util::valve::lock_cursor() : util::valve::unlock_cursor();
    }

    void setup() {
        auto& io = ImGui::GetIO();
        io.LogFilename = NULL;
        io.IniFilename = NULL;
        io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange; // fix annoying cursor flickering
    }
} // namespace hack::menu
