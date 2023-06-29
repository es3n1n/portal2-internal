#include "vmt.hpp"
#include "util/logger/logger.hpp"

namespace util::hooking {
    namespace detail {
        region_protector::region_protector(void* base, size_t length, mem::e_mem_protection flags) {
            _base = base;
            _length = length;

            // @todo: @es3n1n: we should probably old protection here too, but thing is that on linux i'd have to parse some strings in order to get page
            //  protection. I'm looking for a more convenient way for now, not sure if that's possible though.
            mem::protect_memory(_base, _length, flags);
        }
        region_protector::~region_protector() {
            mem::protect_memory(_base, _length, mem::MEM_READ);
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
        vftbl_len = mem::estimate_virtual_table_length(old_vftbl) * sizeof(std::uintptr_t);

        new_vftbl = new std::uintptr_t[vftbl_len + 1]();

        memcpy(&new_vftbl[1], old_vftbl, vftbl_len * sizeof(std::uintptr_t));

        auto guard = detail::region_protector{class_base, sizeof(std::uintptr_t), mem::MEM_READ_WRITE};
        new_vftbl[0] = old_vftbl[-1];
        *reinterpret_cast<std::uintptr_t**>(class_base) = &new_vftbl[1];
    }

    void vmt::unhook() {
        if (old_vftbl == nullptr)
            return;

        auto guard = detail::region_protector{class_base, sizeof(std::uintptr_t), mem::MEM_READ_WRITE};

        *reinterpret_cast<std::uintptr_t**>(class_base) = old_vftbl;

        old_vftbl = nullptr;
    }
} // namespace util::hooking
