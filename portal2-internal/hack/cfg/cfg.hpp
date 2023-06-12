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
    void sync_rainbow();
    void randomize_rainbow();

    void read(std::string path);
    void save(std::string path);
    std::string& get_path(std::string& path);

    //
    inline std::vector<cfg_item_t<bool>> _bools = {};
    inline std::vector<cfg_item_t<float>> _floats = {};
    inline std::vector<cfg_item_t<int>> _ints = {};
    inline std::vector<cfg_item_t<std::uint8_t>> _bytes = {};
    inline std::vector<color_t*> _cols = {};

    //
    template <typename t>
    inline void push(t* ptr, std::string_view name) {
        if constexpr (std::is_same_v<std::remove_cv_t<t>, bool>) {
            _bools.emplace_back(cfg_item_t(ptr, name));
        } else if constexpr (std::is_same_v<std::remove_cv_t<t>, float>) {
            _floats.emplace_back(cfg_item_t(ptr, name));
        } else if constexpr (std::is_same_v<std::remove_cv_t<t>, std::uint8_t>) {
            _bytes.emplace_back(cfg_item_t(ptr, name));
        } else if constexpr (std::is_integral_v<std::remove_cv_t<t>> && sizeof(t) <= sizeof(int)) {
            _ints.emplace_back(cfg_item_t(ptr, name));
        } else {
            _ints.emplace_back(cfg_item_t(ptr, name)); // oh no
        }
    }

    //
    constexpr std::string_view _dir = "c:\\portal2-internal";
} // namespace hack::cfg
