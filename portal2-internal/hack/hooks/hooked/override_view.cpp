#include "hack/features/features.hpp"
#include "hack/hooks/hooks.hpp"
#include "sdk/portal.hpp"

namespace hack::hooks::hooked {
    void __stdcall override_view(c_view_setup* setup) {
        static auto o = vmt::clientmode.original<void(__stdcall*)(c_view_setup*)>(18);

        setup->m_fov = opts::fov_value;
        
        o(setup);
    }
} // namespace hack::hooks::hooked
