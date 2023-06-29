#pragma once
#include "util/mem/mem.hpp"
#include <cstdint>
#include <memory>
#include <stdexcept>

namespace util::hooking {
    namespace detail {
        class region_protector {
        public:
            region_protector(void* base, size_t length, mem::e_mem_protection flags);
            ~region_protector();
        private:
            void* _base;
            size_t _length;
        };
    } // namespace detail

    class vmt {
    public:
        vmt();
        vmt(void* base);
        ~vmt();

        void setup(void* base = nullptr);

        template <typename T>
        void hook(int index, T fun) {
            new_vftbl[index + 1] = reinterpret_cast<std::uintptr_t>(fun);
        }

        void unhook();

        template <typename T>
        T original(int index) {
            return reinterpret_cast<T>(old_vftbl[index]);
        }
    private:
        void* class_base;
        std::size_t vftbl_len;
        std::uintptr_t* new_vftbl;
        std::uintptr_t* old_vftbl;
    };
} // namespace util::hooking
