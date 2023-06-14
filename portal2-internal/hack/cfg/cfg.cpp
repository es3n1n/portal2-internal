#include <filesystem>
#include <format>
#include <fstream>
#include <imgui.h>
#include <random>

#include "hack/cfg/cfg.hpp"
#include "hack/cfg/detail/json.hpp"
#include "util/cast/cast.hpp"

namespace hack::cfg {
    namespace {
        template <typename T>
        struct packed_var_t {
        public:
            T* ptr;
            std::string_view fmt;
        };

        template <typename T, typename... Variadic>
        inline void push_packed_vars(const std::string_view prefix, packed_var_t<T> var, Variadic... variadic) {
            push(var.ptr, std::vformat(var.fmt, std::make_format_args(prefix)));

            if constexpr (sizeof...(Variadic))
                push_packed_vars(prefix, variadic...);
        }

        // @fixme: -
        void push_color(color_t* col, const std::string_view prefix) {
            // clang-format off
            push_packed_vars(prefix, 
                packed_var_t{&col->r, "{}_r"},
                packed_var_t{&col->g, "{}_g"},
                packed_var_t{&col->b, "{}_b"},
                packed_var_t{&col->a, "{}_a"},
                packed_var_t{&col->rainbow.enabled, "{}_rainbow"}
            );
            // clang-format on

            _cols.emplace_back(col);
        }

        // @fixme: -
        void push_chams(opts::chams_opts_t* opts, const std::string_view prefix) {
            // clang-format off
            push_packed_vars(prefix, 
                packed_var_t{&opts->m_enabled, "{}_enabled"},
                packed_var_t{&opts->m_material, "{}_material"}
            );
            // clang-format on

            push_color(&opts->m_color, prefix);
        }

        // @fixme: -
        void push_portals(opts::portal_colors_t* opts, const std::string_view prefix) {
            for (std::size_t i = 0; i < 2; ++i)
                push_color(&opts->at(i), std::vformat("{}_{}", std::make_format_args(prefix, i)));
        }
    } // namespace

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

        push_portals(&opts::portal_colors[0], "misc_portal_1");
        push_portals(&opts::portal_colors[1], "misc_portal_2");

        read("config"); // load default cfg

        randomize_rainbow();
    }

    void apply_rainbow() {
        for (auto* col : _cols) {
            if (!col->rainbow.enabled)
                continue;

            col->rainbow.increment();
            col->apply(color_t::from_hsb(col->rainbow.value, .99f, 1.f).replace_a(col->a));
        }
    }

    void sync_rainbow() {
        for (auto* col : _cols)
            col->rainbow.reset();
    }

    void randomize_rainbow() {
        // @note: @es3n1n:
        // ayo shout out to kaspersky lab and their extremely-safe password generators
        static std::mt19937 _rnd(static_cast<unsigned int>(time(nullptr)));

        for (auto* col : _cols)
            col->rainbow.value = (_rnd() % 100) / 100.f;
    }

    std::string& get_path(std::string& path) {
        std::filesystem::create_directory(_dir);
        path = std::string{_dir} + "\\" + path + ".json";
        return path;
    }

    namespace {
        template <typename t>
        inline void deserialize(const nlohmann::json& json, std::vector<cfg_item_t<t>> vec) {
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
        deserialize(data, _bytes);
    }

#define SERIALIZE_TYPE(name) \
    for (auto& x : name)     \
        data[x.m_name] = *x.m_ptr;

    void save(std::string path) {
        path = get_path(path);

        nlohmann::json data;

        SERIALIZE_TYPE(_bools);
        SERIALIZE_TYPE(_floats);
        SERIALIZE_TYPE(_ints);
        SERIALIZE_TYPE(_bytes);

        std::ofstream reader(path);
        reader.clear();
        reader << std::setw(4) << data << std::endl;
        reader.close();
    }

#undef SERIALIZE_TYPE
} // namespace hack::cfg