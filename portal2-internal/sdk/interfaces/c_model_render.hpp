#pragma once
#include "util/math/math.hpp"
#include "util/mem/mem.hpp"

struct model_info_t {
private:
    [[maybe_unused]] std::uint8_t __pad[4];
public:
    char m_name[260];
};

struct model_render_info_t {
private:
    [[maybe_unused]] std::uint8_t __pad[0x1C];
public:
    model_info_t* m_model;
};

class i_material;

enum class override_type_t : int {
    OVERRIDE_NORMAL = 0,
    OVERRIDE_BUILD_SHADOWS,
    OVERRIDE_DEPTH_WRITE,
    OVERRIDE_SELECTIVE,
    OVERRIDE_SSAO_DEPTH_WRITE,
};

// CModelRender: IVModelRender, CManagedDataCacheClient<CColorMeshData,colormeshparams_t,CColorMeshData *>, CDefaultDataCacheClient, IDataCacheClient
class c_model_render {
public:
    // @xref: 55 8B EC 8B 55 10 8B 0D ?? ?? ?? ?? 8B 01 8B 40 40 (engine.dll)
    void forced_material_override(i_material* material, override_type_t override_type = override_type_t::OVERRIDE_NORMAL) {
        return util::mem::virtual_function<void(__thiscall*)(void*, i_material*, override_type_t)>(this, 1)(this, material, override_type);
    }
};
