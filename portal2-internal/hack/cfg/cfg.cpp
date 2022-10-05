#include "cfg.hpp"
#include "detail/json.hpp"
#include <filesystem>
#include <fstream>

namespace hack::cfg {
    void init() {
        push(&opts::bhop, "misc_bhop");
        push(&opts::autostrafer, "misc_strafer");
        push(&opts::airacceleration_fix, "misc_airacceleration_fix");
        push(&opts::airacceleration_value, "misc_airacceleration_value");

        read("config");
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
