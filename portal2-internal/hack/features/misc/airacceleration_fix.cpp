#include "../../cfg/cfg.h"
#include "misc.h"

namespace hack::features::misc {
    namespace {
        uint8_t orig_bytes[7];

        __forceinline void patch() {
            uint8_t shellcode[] = {
                0xB8, 0x37, 0x13, 0x37, 0x13, // mov eax, 0x13371337
                0xFF, 0xE0 // jmp eax
            };

            *reinterpret_cast<std::uintptr_t*>(shellcode + 1) = portal::patterns::airmove_velocity_check.offset(0x8D);

            // save orig bytes
            //
            memcpy(orig_bytes, portal::patterns::airmove_velocity_check.cast<void*>(), sizeof(orig_bytes));

            // apply patch
            //
            DWORD old;
            VirtualProtect(portal::patterns::airmove_velocity_check.cast<void*>(), sizeof(shellcode), PAGE_EXECUTE_READWRITE, &old);
            memcpy(portal::patterns::airmove_velocity_check.cast<void*>(), shellcode, sizeof(shellcode));
            VirtualProtect(portal::patterns::airmove_velocity_check.cast<void*>(), sizeof(shellcode), old, &old);
            FlushInstructionCache(reinterpret_cast<HANDLE>(-1), portal::patterns::airmove_velocity_check.cast<void*>(), sizeof(shellcode));
        }

        __forceinline void restore() {
            DWORD old;
            VirtualProtect(portal::patterns::airmove_velocity_check.cast<void*>(), sizeof(orig_bytes), PAGE_EXECUTE_READWRITE, &old);
            memcpy(portal::patterns::airmove_velocity_check.cast<void*>(), orig_bytes, sizeof(orig_bytes));
            VirtualProtect(portal::patterns::airmove_velocity_check.cast<void*>(), sizeof(orig_bytes), old, &old);
        }
    } // namespace

    void airacceleration_fix() {
        if (cfg::opts::airacceleration_fix) {
            patch();
        } else {
            restore();
        }
    }
} // namespace hack::features::misc