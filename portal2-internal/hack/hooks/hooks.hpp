#pragma once
#include "hack/hack.hpp"
#include "sdk/interfaces/c_clientmode.hpp"
#include <d3d9.h>

namespace hack::hooks {
    namespace hooked {
        void __stdcall create_move(int sequence_number, float input_sample_frametime, bool active);
        long __stdcall present(IDirect3DDevice9* device, RECT* src_rect, RECT* dest_rect, HWND dest_wnd_override, RGNDATA* dirty_region);
        long __stdcall reset(IDirect3DDevice9* pthis, D3DPRESENT_PARAMETERS* params);
        void __stdcall override_view(c_view_setup* setup);
        void __fastcall draw_model_execute(c_model_render* pthis, void* edx, void* context, void* state, model_render_info_t* info, void* matrix);
    } // namespace hooked

    namespace detours {
        void setup();
        void unhook();
    } // namespace detours

    namespace vmt {
        inline util::hooking::vmt hl_client;
        inline util::hooking::vmt dx9;
        inline util::hooking::vmt clientmode;
        inline util::hooking::vmt model_render;

        void setup();
        void unhook();
    } // namespace vmt

    void setup();
    void unhook();
} // namespace hack::hooks