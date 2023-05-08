#include "misc.hpp"

#include "hack/cfg/opts.hpp"

namespace hack::features::misc {
    namespace {
        static constinit uint8_t orig_bytes[7] = {0};

        __forceinline void patch() {
            uint8_t shellcode[] = {
                0xB8, 0x37, 0x13, 0x37, 0x13, // mov eax, portal::sig::airmove_velocity_check_exit
                0xFF, 0xE0 // jmp eax
            };
            *reinterpret_cast<std::uintptr_t*>(shellcode + 1) = portal::sig::airmove_velocity_check_exit;

            static_assert(sizeof(shellcode) == sizeof(orig_bytes));
            util::mem::patch_text_section(portal::sig::airmove_velocity_check, shellcode, sizeof(shellcode), orig_bytes);
        }

        __forceinline void restore() {
            util::mem::patch_text_section(portal::sig::airmove_velocity_check, orig_bytes, sizeof(orig_bytes));
        }
    } // namespace

    void airacceleration_fix() {
        return opts::airacceleration_fix ? patch() : restore();
    }
} // namespace hack::features::misc