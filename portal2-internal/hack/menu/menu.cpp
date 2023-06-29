#include "menu.hpp"
#include "hack/cfg/cfg.hpp"
#include "hack/hack.hpp"
#include "util/util.hpp"
#include <Windows.h>

#if defined(__clang__)
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wformat-security" // ignore ImGui::Text formats
#endif

namespace hack::menu {
    constexpr float_t kDefaultAirAccelerationValue = 5.f;
    constexpr float_t kCSGOAirAccelerationValue = 12.f;
    constexpr float_t kBhopAirAccelerationValue = 10000.f;
    constexpr float_t kDefaultFOVValue = 90.f;

    namespace {
        inline bool color_edit(const char* label, color_t* col, ImGuiColorEditFlags flags, const char* id = nullptr) {
            ImGui::PushID(!id ? label : id);
            auto clr = ImVec4(col->r / 255.f, col->g / 255.f, col->b / 255.f, col->a / 255.f);

            ImGuiColorEditFlags color_button_flags = ImGuiColorEditFlags_NoTooltip;
            if (!(flags & ImGuiColorEditFlags_NoAlpha))
                color_button_flags |= ImGuiColorEditFlags_AlphaPreview;

            bool openPopup = ImGui::ColorButton("##btn", clr, color_button_flags);
            ImGui::SameLine();
            ImGui::Text(label);

            if (openPopup)
                ImGui::OpenPopup("##popup");

            if (ImGui::BeginPopup("##popup")) {
                ImGuiColorEditFlags color_picker_flags = ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs;
                if (!(flags & ImGuiColorEditFlags_NoAlpha))
                    color_picker_flags |= ImGuiColorEditFlags_AlphaBar;

                if (ImGui::ColorPicker4("##picker", &clr.x, color_picker_flags))
                    col->apply(static_cast<color_t::channel_flt_t>(clr.x), static_cast<color_t::channel_flt_t>(clr.y),
                               static_cast<color_t::channel_flt_t>(clr.z), static_cast<color_t::channel_flt_t>(clr.w));

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

                ImGui::Checkbox("Rainbow", &col->rainbow.enabled);

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

        ImGui::Separator();

        ImGui::SetNextItemWidth(120.f);
        if (ImGui::InputFloat("airacceleration", &opts::airacceleration_value, 1.f, 5.f, "%1.f") ||
            (first_render && fabsf(opts::airacceleration_value - kDefaultAirAccelerationValue) > 0.01f))
            features::misc::apply_acceleration();

        auto custom_acceleration_btn = [](const char* name, const float_t value) -> void {
            ImGui::SameLine();
            if (!ImGui::Button(name))
                return;
            features::misc::apply_acceleration(value);
        };

        custom_acceleration_btn("DEFAULT", kDefaultAirAccelerationValue);
        custom_acceleration_btn("CSGO", kCSGOAirAccelerationValue);
        custom_acceleration_btn("BHOP", kBhopAirAccelerationValue);

        ImGui::Separator();

        ImGui::SliderFloat("FOV", &opts::fov_value, 10.f, 160.f);
        ImGui::SameLine();
        if (ImGui::Button("Reset"))
            opts::fov_value = kDefaultFOVValue;

        ImGui::Separator();

        auto chams_settings = [=](const std::string_view name, opts::chams_opts_t* ptr) -> void {
            ImGui::PushID(name.data());
            ImGui::Checkbox(name.data(), &ptr->m_enabled);
            ImGui::SameLine();
            color_edit("Color", &ptr->m_color, 0);
            ImGui::SameLine();

            ImGui::SetNextItemWidth(120.f);
            ImGui::Combo("Type", &ptr->m_material, "Normal\0Flat\0");

            ImGui::PopID();
        };

        chams_settings("Portalgun Chams", &opts::portal_gun_chams);
        chams_settings("Chell Chams", &opts::chell_chams);
        chams_settings("Wheatley Chams", &opts::wheatley_chams);

        ImGui::Separator();

        ImGui::Checkbox("Mat Ambient Light modification", &opts::mat_ambient_light_enabled);
        ImGui::SameLine();
        color_edit("Color", &opts::mat_ambient_light_value, 0, "matambient");

        ImGui::Separator();

        ImGui::Checkbox("Trails", &opts::trails);
        ImGui::SameLine();
        color_edit("Color", &opts::trails_color, 0, "trails");
        ImGui::SameLine();

        ImGui::SetNextItemWidth(120.f);
        ImGui::SliderFloat("Life time", &opts::trails_life_time, 1.f, 15.f);

        ImGui::Separator();

        // @fixme: @es3n1n: remove prefix_col_1/prefix_col_2
        const auto portal_colors_settings = [](const std::string_view prefix, std::size_t index, const std::string_view prefix_col_1,
                                               const std::string_view prefix_col_2) -> void {
            ImGui::PushID(prefix.data());

            ImGui::Text(prefix.data());
            ImGui::SameLine();

            color_edit("Portal 1", &opts::portal_colors[index].m_portal_1, ImGuiColorEditFlags_NoAlpha, prefix_col_1.data());
            ImGui::SameLine();
            color_edit("Portal 2", &opts::portal_colors[index].m_portal_2, ImGuiColorEditFlags_NoAlpha, prefix_col_2.data());

            ImGui::PopID();
        };

        portal_colors_settings("Player1:", 0, "p1c1", "p1c2");
        portal_colors_settings("Player2:", 1, "p2c1", "p2c2");

        ImGui::Separator();

        if (ImGui::Button("save"))
            cfg::save("config");
        ImGui::SameLine();
        if (ImGui::Button("load"))
            cfg::read("config");

        ImGui::Separator();

        if (ImGui::Button("randomize rainbow"))
            cfg::randomize_rainbow();
        ImGui::SameLine();
        if (ImGui::Button("sync rainbow"))
            cfg::sync_rainbow();

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

#if defined(__clang__)
    #pragma clang diagnostic pop
#endif
