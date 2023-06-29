#include "util/mem/mem.hpp"
#include "util/mem/addr/addr.hpp"

#if IS_WIN
namespace util::mem {
    void patch_text_section(mem::addr_t dst, uint8_t* src, size_t len, uint8_t* orig) {
        // save orig bytes
        //
        if (orig)
            memcpy(orig, src, len);

        // change protection so we could overwrite stufff
        //
        DWORD old;
        VirtualProtect(dst.cast<void*>(), len, PAGE_EXECUTE_READWRITE, &old);

        // apply patch
        //
        memcpy(dst.cast<void*>(), src, len);

        // restore protection + flush instruction cache
        //
        VirtualProtect(dst.cast<void*>(), len, old, &old);
        FlushInstructionCache(reinterpret_cast<HANDLE>(-1), dst.cast<void*>(), len);
    }
} // namespace util::mem
#endif
