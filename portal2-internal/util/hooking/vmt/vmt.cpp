#include "vmt.h"

namespace util::hooking {
    namespace detail {
        region_protector::region_protector(void* base, size_t len, std::uint32_t flags) {
            _base = base;
            _length = len;
            VirtualProtect(base, len, flags, (PDWORD)&_old);
        }
        region_protector::~region_protector() {
            VirtualProtect(_base, _length, _old, (PDWORD)&_old);
        }
    } // namespace detail

    vmt::vmt(): class_base(nullptr), vftbl_len(0), new_vftbl(nullptr), old_vftbl(nullptr) { }
    vmt::vmt(void* base): class_base(base), vftbl_len(0), new_vftbl(nullptr), old_vftbl(nullptr) { }
    vmt::~vmt() {
        unhook();
        delete[] new_vftbl;
    }

    void vmt::setup(void* base) {
        if (base != nullptr)
            class_base = base;

        old_vftbl = *reinterpret_cast<std::uintptr_t**>(class_base);
        vftbl_len = estimate_vftbl_length(old_vftbl) * sizeof(std::uintptr_t);

        new_vftbl = new std::uintptr_t[vftbl_len + 1]();

        std::memcpy(&new_vftbl[1], old_vftbl, vftbl_len * sizeof(std::uintptr_t));

        auto guard = detail::region_protector{class_base, sizeof(std::uintptr_t), PAGE_READWRITE};
        new_vftbl[0] = old_vftbl[-1];
        *reinterpret_cast<std::uintptr_t**>(class_base) = &new_vftbl[1];
    }

    std::size_t vmt::estimate_vftbl_length(std::uintptr_t* vftbl_start) {
        MEMORY_BASIC_INFORMATION memInfo = {NULL};
        int m_nSize = -1;
        do {
            m_nSize++;
            VirtualQuery(reinterpret_cast<LPCVOID>(vftbl_start[m_nSize]), &memInfo, sizeof(memInfo));
        } while (memInfo.Protect == PAGE_EXECUTE_READ || memInfo.Protect == PAGE_EXECUTE_READWRITE);

        return m_nSize;
    }

    void vmt::unhook() {
        if (old_vftbl == nullptr)
            return;

        auto guard = detail::region_protector{class_base, sizeof(std::uintptr_t), PAGE_READWRITE};
        try {
            *reinterpret_cast<std::uintptr_t**>(class_base) = old_vftbl;
        } catch (...) { }
        old_vftbl = nullptr;
    }
} // namespace util::hooking
