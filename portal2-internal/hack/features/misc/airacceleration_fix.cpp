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

            // save orig bytes
            //
            memcpy(orig_bytes, portal::sig::airmove_velocity_check.cast<void*>(), sizeof(orig_bytes));
            static_assert(sizeof(orig_bytes) == sizeof(shellcode));

            // change protection so we could overwrite this fn
            //
            DWORD old;
            VirtualProtect(portal::sig::airmove_velocity_check.cast<void*>(), sizeof(shellcode), PAGE_EXECUTE_READWRITE, &old);

            // apply patch
            //
            memcpy(portal::sig::airmove_velocity_check.cast<void*>(), shellcode, sizeof(shellcode));

            // restore protection + flush instruction cache
            //
            VirtualProtect(portal::sig::airmove_velocity_check.cast<void*>(), sizeof(shellcode), old, &old);
            FlushInstructionCache(reinterpret_cast<HANDLE>(-1), portal::sig::airmove_velocity_check.cast<void*>(), sizeof(shellcode));
        }

        __forceinline void restore() {
            // change protection
            //
            DWORD old;
            VirtualProtect(portal::sig::airmove_velocity_check.cast<void*>(), sizeof(orig_bytes), PAGE_EXECUTE_READWRITE, &old);

            // restore patch
            //
            memcpy(portal::sig::airmove_velocity_check.cast<void*>(), orig_bytes, sizeof(orig_bytes));

            // restore protection
            VirtualProtect(portal::sig::airmove_velocity_check.cast<void*>(), sizeof(orig_bytes), old, &old);
        }
    } // namespace

    void airacceleration_fix() {
        return opts::airacceleration_fix ? patch() : restore();
    }
} // namespace hack::features::misc