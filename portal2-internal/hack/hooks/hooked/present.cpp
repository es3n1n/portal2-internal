#include "hack/hooks/hooks.hpp"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"
#include <mutex>

namespace hack::hooks::hooked {
    namespace {
        constexpr std::uint32_t kColorWriteDefaultValue = -1;
        constexpr std::uint32_t kSrgbWriteDefaultValue = 0;

        // @note: @es3n1n: we should overwrite D3DRS_COLORWRITEENABLE/D3DRS_SRGBWRITEENABLE
        // in order to disable source engine color correction
        struct scoped_color_correction_disabler_t {
        public:
            constexpr scoped_color_correction_disabler_t() = default;

            inline scoped_color_correction_disabler_t(IDirect3DDevice9* device): _device(device), _color_write_value(0u), _srgb_write_value(0u) {
                backup();
                apply();
            }

            inline ~scoped_color_correction_disabler_t() {
                restore();
            }
        public:
            __forceinline void backup() {
                _device->GetRenderState(D3DRS_COLORWRITEENABLE, &_color_write_value);
                _device->GetRenderState(D3DRS_SRGBWRITEENABLE, &_srgb_write_value);
            }

            __forceinline void apply() {
                _device->SetRenderState(D3DRS_COLORWRITEENABLE, kColorWriteDefaultValue);
                _device->SetRenderState(D3DRS_SRGBWRITEENABLE, kSrgbWriteDefaultValue);
            }

            __forceinline void restore() {
                _device->SetRenderState(D3DRS_COLORWRITEENABLE, _color_write_value);
                _device->SetRenderState(D3DRS_SRGBWRITEENABLE, _srgb_write_value);
            }
        private:
            IDirect3DDevice9* _device = nullptr;
            DWORD _color_write_value = 0u, _srgb_write_value = 0u;
        };
    } // namespace

    namespace {
        __forceinline void ensure_init(IDirect3DDevice9* device) {
            static std::once_flag fl;
            std::call_once(fl, [=]() -> void {
                ImGui::CreateContext();
                ImGui_ImplDX9_Init(device);
                ImGui_ImplWin32_Init(util::input::win);

                menu::setup();
            });
        }

        __forceinline void draw(IDirect3DDevice9* device) {
            auto color_correction_fix = scoped_color_correction_disabler_t(device);

            ImGui_ImplDX9_NewFrame();
            ImGui_ImplWin32_NewFrame();

            ImGui::GetIO().MouseDrawCursor = menu::opened;

            ImGui::NewFrame();

            cfg::apply_rainbow();
            menu::render();

            ImGui::EndFrame();
            ImGui::Render();
            ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
        }
    } // namespace

    long __stdcall present(IDirect3DDevice9* device, RECT* src_rect, RECT* dest_rect, HWND dest_wnd_override, RGNDATA* dirty_region) {
        static auto o = vmt::dx9.original<decltype(&present)>(17);

        ensure_init(device);
        draw(device);

        return o(device, src_rect, dest_rect, dest_wnd_override, dirty_region);
    }
} // namespace hack::hooks::hooked
