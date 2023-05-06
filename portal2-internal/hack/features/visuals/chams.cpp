#include "hack/cfg/opts.hpp"
#include "util/hash/fnv.hpp"
#include "visuals.hpp"

#include <fstream>

namespace hack::features::visuals {
    namespace {
        i_material* mat_normal = nullptr;
        i_material* mat_flat = nullptr;

        __forceinline void ensure_init() {
            static std::once_flag fl;

            std::call_once(fl, [=]() -> void { //
                // fixme:
                std::ofstream{"portal2/materials/chamsNormal.vmt"} << "VertexLitGeneric { }";
                std::ofstream{"portal2/materials/chamsFlat.vmt"} << "UnlitGeneric { }";

                mat_normal = portal::material_system->find_material("chamsNormal");
                mat_flat = portal::material_system->find_material("chamsFlat");
            });
        }
    } // namespace

    __forceinline void apply_material(opts::chams_opts_t& opts) {
        if (!opts.m_enabled)
            return;

        i_material* material = nullptr;
        switch (opts.m_material) {
        case 0:
            material = mat_normal;
            break;
        case 1:
            material = mat_flat;
            break;
        default:
#ifdef _DEBUG
            __debugbreak(); // unknown material
#endif
            break;
        }

        material->color_modulate(opts.m_color.r / 255.f, opts.m_color.g / 255.f, opts.m_color.b / 255.f);
        material->alpha_modulate(opts.m_color.a / 255.f);

        portal::model_render->forced_material_override(material);
    }

    void chams(c_model_render* pthis, void* ctx, void* state, model_render_info_t* info, void* matrix, void* original_dme) {
        const auto orig = reinterpret_cast<void(__thiscall*)(c_model_render*, void*, void*, void*, void*)>(original_dme);

        ensure_init();

        switch (fnv32::hash_runtime(info->m_model->m_name)) {
        case FNV32("models/weapons/v_portalgun.mdl"):
        case FNV32("models/weapons/w_portalgun.mdl"):
            apply_material(opts::portal_gun_chams);
            break;

        case FNV32("models/player/chell/player.mdl"):
            apply_material(opts::chell_chams);
            break;

        case FNV32("models/npcs/personality_sphere/personality_sphere.mdl"):
            apply_material(opts::wheatley_chams);
            break;

        default:
            // util::logger::debug("Ignoring model '%s'", info->m_model->m_name);
            break;
        }
    }
} // namespace hack::features::visuals
