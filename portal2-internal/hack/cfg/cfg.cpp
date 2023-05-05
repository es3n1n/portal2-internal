#include "cfg.hpp"
#include "detail/json.hpp"
#include <filesystem>
#include <format>
#include <fstream>
#include <imgui.h>

namespace hack::cfg {
    // @fixme: -
    __forceinline void push_chams_opts(const std::string_view prefix, opts::chams_opts_t& opts) {
        push(&opts.m_enabled, std::format("{}_enabled", prefix));

        push(&opts.m_material, std::format("{}_material", prefix));

        push(&opts.m_color.r, std::format("{}_r", prefix));
        push(&opts.m_color.g, std::format("{}_g", prefix));
        push(&opts.m_color.b, std::format("{}_b", prefix));
        push(&opts.m_color.a, std::format("{}_a", prefix));
        push(&opts.m_color.rainbow, std::format("{}_rainbow", prefix));

        _cols.emplace_back(&opts.m_color);
    }

    void init() {
        push(&opts::bhop, "misc_bhop");
        push(&opts::autostrafer, "misc_strafer");
        push(&opts::airacceleration_fix, "misc_airacceleration_fix");
        push(&opts::airacceleration_value, "misc_airacceleration_value");
        push(&opts::fov_value, "misc_fov_value");

        push_chams_opts("portal_gun_chams", opts::portal_gun_chams);
        push_chams_opts("chell_chams", opts::chell_chams);
        push_chams_opts("wheatley_chams", opts::wheatley_chams);

        read("config"); // load default cfg
    }

    void apply_rainbow() {
        for (auto* col : _cols) {
            if (!col->rainbow)
                continue;

            col->rainbow_value += 0.1 * ImGui::GetIO().DeltaTime;
            if (col->rainbow_value > 1.f)
                col->rainbow_value = 0.f;

            auto new_col = color_t::from_hsb(col->rainbow_value, 0.99f, 1.f);
            col->apply(new_col.r, new_col.g, new_col.b, col->a);
        }
    }

    std::string& get_path(std::string& path) {
        std::filesystem::create_directory(_dir);
        path = std::string{_dir} + "\\" + path + ".json";
        return path;
    }

    namespace {
        template <typename t>
        __forceinline void deserialize(const nlohmann::json& json, std::vector<cfg_item_t<t>> vec) {
            std::for_each(vec.begin(), vec.end(), [json](const auto& it) -> void {
                if (json.find(it.m_name) == json.end())
                    return;
                *it.m_ptr = json[it.m_name].get<t>();
            });
        }
    } // namespace

    void read(std::string path) {
        path = get_path(path);
        if (!std::filesystem::exists(path))
            return;

        std::ifstream reader(path);
        nlohmann::json data;
        reader >> data;
        reader.close();

        deserialize(data, _bools);
        deserialize(data, _floats);
    }

    void save(std::string path) {
        path = get_path(path);

        nlohmann::json data;

        for (auto& b : _bools)
            data[b.m_name] = *b.m_ptr;
        for (auto& f : _floats)
            data[f.m_name] = *f.m_ptr;

        std::ofstream reader(path);
        reader.clear();
        reader << std::setw(4) << data << std::endl;
        reader.close();
    }
} // namespace hack::cfg
