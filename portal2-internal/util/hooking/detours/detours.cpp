#include "detours.hpp"
#include "util/logger/logger.hpp"

#define MH_ASSERT_BEGIN std::uint32_t stat;
#define MH_ASSERT(cond, err)        \
    if (stat = cond; stat != MH_OK) \
        return L_ERROR(err ": %i", stat);

//
// No detours for now as we are not using them anyway
//

namespace util::hooking::detour {
    void init() {
        // MH_ASSERT_BEGIN;
        // MH_ASSERT(MH_Initialize(), "Unable to initialize");
    }

    void create(mem::addr_t& target, void* detour, void** orig) {
        return create(target.cast<void*>(), detour, orig);
    }

    void create(void* target, void* detour, void** orig) {
        // MH_ASSERT_BEGIN;
        // MH_ASSERT(MH_CreateHook(target, detour, orig), "Unable to create hook");
        // MH_ASSERT(MH_EnableHook(target), "Unable to enable hook");
    }

    void remove(void* target) {
        // MH_ASSERT_BEGIN;
        // MH_ASSERT(MH_DisableHook(target), "Unable to disable hooks");
    }
} // namespace util::hooking::detour

#undef MH_ASSERT_BEGIN
#undef MH_ASSERT
