#include "menu.hpp"
#include "hack/cfg/cfg.hpp"
#include "hack/hack.hpp"
#include "util/util.hpp"
#include <Windows.h>

namespace hack::menu {
    constexpr float_t kDefaultAirAccelerationValue = 5.f;
    constexpr float_t kCSGOAirAccelerationValue = 12.f;
    constexpr float_t kBhopAirAccelerationValue = 10000.f;
    constexpr float_t kDefaultFOVValue = 90.f;

    namespace {
        inline bool color_edit(const char* label, color_t* col, ImGuiColorEditFlags flags) {
            ImGui::PushID(label);
            auto clr = ImVec4(col->r / 255.f, col->g / 255.f, col->b / 255.f, col->a / 255.f);

            bool openPopup = ImGui::ColorButton("##btn", clr, ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_AlphaPreview);
            ImGui::SameLine();
            ImGui::Text(label);

            if (openPopup)
                ImGui::OpenPopup("##popup");

            if (ImGui::BeginPopup("##popup")) {
                if (ImGui::ColorPicker4("##picker", &clr.x,
                                        ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar))
                    col->apply(clr.x, clr.y, clr.z, clr.w);

                ImGui::Separator();
                ImGui::BeginColumns("##colsinpopup", 4, ImGuiOldColumnFlags_NoBorder);
                ImGui::Text("R: %d", col->r);
                ImGui::NextColumn();
                ImGui::Text("G: %d", col->g);
                ImGui::NextColumn();
                ImGui::Text("B: %d", col->b);
                ImGui::NextColumn();
                ImGui::Text("A: %d", col->a);
                ImGui::EndColumns();
                ImGui::Separator();

                ImGui::Checkbox("Rainbow", &col->rainbow);

                ImGui::EndPopup();
            }
            ImGui::PopID();

            return false;
        }
    } // namespace

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

        ImGui::SliderFloat("FOV", &opts::fov_value, 10.f, 160.f);
        ImGui::SameLine();
        if (ImGui::Button("Reset"))
            opts::fov_value = kDefaultFOVValue;

        ImGui::Spacing();

        auto chams_settings = [=](const std::string_view name, opts::chams_opts_t* ptr) [[msvc::forceinline]] -> void {
            ImGui::PushID(name.data());
            ImGui::Checkbox(name.data(), &ptr->m_enabled);
            ImGui::SameLine();
            color_edit("Color", &ptr->m_color, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoLabel);
            ImGui::Combo("Type", &ptr->m_material, "Normal\0Flat\0");
            ImGui::PopID();
        };

        chams_settings("Portalgun Chams", &opts::portal_gun_chams);
        chams_settings("Chell Chams", &opts::chell_chams);
        chams_settings("Wheatley Chams", &opts::wheatley_chams);

        ImGui::Spacing();

        ImGui::Checkbox("Mat Ambient Light modification", &opts::mat_ambient_light_enabled);
        ImGui::SameLine();
        color_edit("Mat Ambient color", &opts::mat_ambient_light_value, ImGuiColorEditFlags_NoLabel);

        ImGui::Spacing();

        ImGui::Checkbox("Trails", &opts::trails);
        ImGui::SameLine();
        color_edit("Trails color", &opts::trails_color, ImGuiColorEditFlags_NoLabel);
        ImGui::SliderFloat("Trails life time", &opts::trails_life_time, 1.f, 15.f);

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
        return opened ? util::game::lock_cursor() : util::game::unlock_cursor();
    }

    void setup() {
        auto& io = ImGui::GetIO();
        io.LogFilename = NULL;
        io.IniFilename = NULL;
        io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange; // fix annoying cursor flickering
    }
} // namespace hack::menu
