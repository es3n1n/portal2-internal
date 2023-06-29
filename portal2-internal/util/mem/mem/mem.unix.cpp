#include "util/mem/mem.hpp"
#include "util/mem/addr/addr.hpp"

#if IS_UNIX
#include <malloc.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

namespace util::mem {
    int convert_from_mem_protection(e_mem_protection protection) {
        int result = MEM_NONE;
        if (protection & MEM_READ)
            result |= PROT_READ;
        if (protection & MEM_WRITE)
            result |= PROT_WRITE;
        if (protection & MEM_EXECUTE)
            result |= PROT_EXEC;
        return result;
    }

    e_mem_protection convert_to_mem_protection(int protection) {
        int result = MEM_NONE;
        if (protection & PROT_READ)
            result |= MEM_READ;
        if (protection & PROT_WRITE)
            result |= MEM_WRITE;
        if (protection & PROT_EXEC)
            result |= MEM_EXECUTE;
        return static_cast<e_mem_protection>(result);
    }

    bool protect_memory(void* mem, size_t len, e_mem_protection protection) {
        return mprotect(mem, len, convert_from_mem_protection(protection)) != -1;
    }

    void patch_text_section(void* dst, const uint8_t* src, size_t len, uint8_t* orig) {
        // save orig bytes
        //
        if (orig)
            memcpy(orig, src, len);

        // change protection so we could overwrite stufff
        //
        protect_memory(dst, len, MEM_EXECUTE_READ_WRITE);

        // apply patch
        //
        memcpy(dst, src, len);

        // restore protection
        //
        protect_memory(dst, len, MEM_EXECUTE_READ);
    }
} // namespace util::mem
#endif
