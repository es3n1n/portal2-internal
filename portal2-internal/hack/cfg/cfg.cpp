#include "cfg.hpp"
#include "detail/json.hpp"
#include <filesystem>
#include <format>
#include <fstream>
#include <imgui.h>

namespace hack::cfg {
    // @fixme: -
    __forceinline void push_color(color_t* col, const std::string_view prefix) {
        push(&col->r, std::format("{}_r", prefix));
        push(&col->g, std::format("{}_g", prefix));
        push(&col->b, std::format("{}_b", prefix));
        push(&col->a, std::format("{}_a", prefix));
        push(&col->rainbow, std::format("{}_rainbow", prefix));

        _cols.emplace_back(col);
    }

    // @fixme: -
    __forceinline void push_chams(opts::chams_opts_t* opts, const std::string_view prefix) {
        push(&opts->m_enabled, std::format("{}_enabled", prefix));
        push(&opts->m_material, std::format("{}_material", prefix));
        push_color(&opts->m_color, prefix);
    }

    void init() {
        push(&opts::bhop, "misc_bhop");
        push(&opts::autostrafer, "misc_strafer");
        push(&opts::airacceleration_fix, "misc_airacceleration_fix");
        push(&opts::airacceleration_value, "misc_airacceleration_value");
        push(&opts::fov_value, "misc_fov_value");

        push_chams(&opts::portal_gun_chams, "portal_gun_chams");
        push_chams(&opts::chell_chams, "chell_chams");
        push_chams(&opts::wheatley_chams, "wheatley_chams");

        push(&opts::mat_ambient_light_enabled, "misc_mat_ambient");
        push_color(&opts::mat_ambient_light_value, "misc_mat_ambient");

        push(&opts::trails, "misc_trails");
        push(&opts::trails_life_time, "misc_trails_life_time");
        push_color(&opts::trails_color, "misc_trails");

        read("config"); // load default cfg
    }

    void apply_rainbow() {
        for (auto* col : _cols) {
            if (!col->rainbow)
                continue;

            col->rainbow_value += 0.1f * ImGui::GetIO().DeltaTime;
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
        deserialize(data, _ints);
    }

    void save(std::string path) {
        path = get_path(path);

        nlohmann::json data;

        for (auto& b : _bools)
            data[b.m_name] = *b.m_ptr;
        for (auto& f : _floats)
            data[f.m_name] = *f.m_ptr;
        for (auto& i : _ints)
            data[i.m_name] = *i.m_ptr;

        std::ofstream reader(path);
        reader.clear();
        reader << std::setw(4) << data << std::endl;
        reader.close();
    }
} // namespace hack::cfg
