#pragma once
#include <cstdint>

namespace util::mem {
    template <typename ptr_type = std::uintptr_t>
    struct memory_address_t {
    public:
        //
        // constructors etc...
        memory_address_t(): m_ptr(ptr_type(0)){};
        memory_address_t(ptr_type v): m_ptr(v){};
        memory_address_t(void* v): m_ptr(ptr_type(v)){};
        memory_address_t(const void* v): m_ptr(ptr_type(v)){};
        ~memory_address_t() = default;

        //
        // operators
        //
        inline operator ptr_type() {
            return m_ptr;
        }

        inline operator void*() {
            return static_cast<void*>(m_ptr);
        }

        inline memory_address_t& operator+=(ptr_type offset) {
            m_ptr += offset;
            return *this;
        }

        inline memory_address_t& operator-=(ptr_type offset) {
            m_ptr -= offset;
            return *this;
        }

        inline memory_address_t operator-(ptr_type offset) {
            return memory_address_t<ptr_type>(m_ptr - offset);
        }

        inline memory_address_t operator+(ptr_type offset) {
            return memory_address_t<ptr_type>(m_ptr + offset);
        }

        //
        // utils
        //
        memory_address_t<ptr_type> offset(ptrdiff_t off) {
            if (!m_ptr)
                return m_ptr;
            return memory_address_t<ptr_type>(m_ptr + off);
        }

        template <typename T>
        T read() {
            return *ptr<T>();
        }

        template <typename T>
        T* ptr() {
            return reinterpret_cast<T*>(m_ptr);
        }

        template <typename T>
        T cast() {
            return reinterpret_cast<T>(m_ptr);
        }

        memory_address_t<ptr_type>& self_get(ptr_type count = 1) {
            if (!m_ptr)
                return *this;

            for (ptr_type i = 0; i < count; i++)
                m_ptr = *reinterpret_cast<ptr_type*>(m_ptr);
            return *this;
        }

        template <typename T = std::int32_t>
        memory_address_t<ptr_type> jmp(ptrdiff_t offset = 0x1) const {
            if (!m_ptr)
                return ptr_type(0);

            ptr_type base = m_ptr + offset;
            auto disp = *reinterpret_cast<T*>(base);

            base += sizeof(T);
            base += disp;

            return ptr_type(base);
        }
    private:
        ptr_type m_ptr;
    };
    using addr_t = mem::memory_address_t<std::uintptr_t>;
} // namespace util::mem