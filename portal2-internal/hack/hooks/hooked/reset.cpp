#include "hack/hooks/hooks.hpp"
#include "imgui_impl_dx9.h"

namespace hack::hooks::hooked {
    long __stdcall reset(IDirect3DDevice9* pthis, D3DPRESENT_PARAMETERS* params) {
        static auto o = vmt::dx9.original<decltype(&reset)>(16);
        ImGui_ImplDX9_InvalidateDeviceObjects();

        auto ret = o(pthis, params);
        ImGui_ImplDX9_CreateDeviceObjects();

        return ret;
    }
} // namespace hack::hooks::hooked
