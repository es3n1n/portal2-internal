#include "hack/hooks/hooks.hpp"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"
#include <mutex>

namespace hack::hooks::hooked {
    long __stdcall present(IDirect3DDevice9* device, RECT* src_rect, RECT* dest_rect, HWND dest_wnd_override, RGNDATA* dirty_region) {
        static auto o = vmt::dx9.original<decltype(&present)>(17);

        if (static bool once_flag = false; !once_flag) {
            ImGui::CreateContext();
            ImGui_ImplDX9_Init(device);
            ImGui_ImplWin32_Init(util::input::win);

            menu::setup();

            ImGuiIO& io = ImGui::GetIO();
            io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange; // fix annoying cursor flickering
            once_flag = true;
        }

        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();

        ImGui::GetIO().MouseDrawCursor = menu::opened;

        ImGui::NewFrame();

        menu::render();

        ImGui::EndFrame();
        ImGui::Render();
        ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

        return o(device, src_rect, dest_rect, dest_wnd_override, dirty_region);
    }
} // namespace hack::hooks::hooked
