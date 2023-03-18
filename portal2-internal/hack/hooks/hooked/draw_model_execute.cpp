#include "hack/features/features.hpp"
#include "hack/hooks/hooks.hpp"

namespace hack::hooks::hooked {
    void __fastcall draw_model_execute(c_model_render* pthis, void* edx, void* context, void* state, model_render_info_t* info, void* matrix) {
        static auto o = vmt::model_render.original<decltype(&draw_model_execute)>(19);

        features::draw_model_execute(pthis, context, state, info, matrix, reinterpret_cast<void*>(o));

        o(pthis, edx, context, state, info, matrix);

        portal::model_render->forced_material_override(nullptr);
    }
} // namespace hack::hooks::hooked
