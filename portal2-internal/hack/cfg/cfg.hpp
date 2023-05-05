#pragma once
#include "opts.hpp"
#include <functional>
#include <string>
#include <vector>

namespace hack::cfg {
    template <typename t>
    struct cfg_item_t {
    public:
        t* m_ptr{};
        std::string m_name{};
    public:
        cfg_item_t(t* ptr, std::string_view name): m_ptr(ptr), m_name(name) { }
        ~cfg_item_t() = default;
    };

    void init();
    void apply_rainbow();

    void read(std::string path);
    void save(std::string path);
    std::string& get_path(std::string& path);

    //
    inline std::vector<cfg_item_t<bool>> _bools = {};
    inline std::vector<cfg_item_t<float>> _floats = {};
    inline std::vector<cfg_item_t<int>> _ints = {};
    inline std::vector<color_t*> _cols = {};

    //
    template <typename t>
    inline cfg_item_t<t>& push(t* ptr, std::string_view name) {
        if constexpr (std::is_same_v<t, bool>) {
            return _bools.emplace_back(cfg_item_t(ptr, name));
        } else if constexpr (std::is_same_v<t, float>) {
            return _floats.emplace_back(cfg_item_t(ptr, name));
        } else if constexpr (std::is_same_v<t, int> || std::is_same_v<t, int32_t>) {
            return _ints.emplace_back(cfg_item_t(ptr, name));
        }
    }

    //
    constexpr std::string_view _dir = "c:\\portal2-internal";
} // namespace hack::cfg
