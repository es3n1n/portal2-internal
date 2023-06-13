#pragma once

#include <cstdint>
#include <limits>

// @note: kehrazy: i don't want to have a util::util namespace,
//                 this is cleaner imo
namespace util {
    namespace detail {
        template <typename T>
        constexpr bool binary_radix = std::numeric_limits<T>::radix == 2;

        template <typename T> concept is_binary_radix = binary_radix<T>;
        template <typename T> concept ieee754_compliant = std::numeric_limits<T>::is_iec559;

        template <typename T> concept is_safe_castable = is_binary_radix<T> && ieee754_compliant<T>;

        template <typename T>
        requires is_safe_castable<T>
        constexpr T exp2(const int& exp) noexcept {
            T result{1.0};

            // look into std::bit_cast
            for (int i{0}; i < exp; i++) {
                result *= 2.f;
            }

            return result;
        }

        template <typename T>
        requires is_safe_castable<T>
        constexpr std::uint16_t exp_bits() noexcept {
            return std::numeric_limits<T>::max_exponent - 1;
        }
    } // namespace detail

    // @note: kehrazy: apparently we have to do this shit,
    //                 std::is_nan is non constexpr
    template <typename T>
    requires detail::is_safe_castable<T>
    [[nodiscard]] constexpr bool is_nan(const T& val) noexcept {
        static_assert(std::numeric_limits<T>::is_iec559, "can't determine is_nan() for a non IEEE-754 compliant type");

        // https://en.cppreference.com/w/cpp/numeric/math/isnan
        return val != val;
    }

    template <typename to_t, typename from_t>
    constexpr from_t lower_bound() noexcept {
        using to_limits = std::numeric_limits<to_t>;
        using from_limits = std::numeric_limits<from_t>;

        static_assert(to_limits::is_integer);
        static_assert(detail::is_binary_radix<to_t>);

        if constexpr (to_limits::is_signed) {
            constexpr int to_bits = to_limits::digits;
            if constexpr (detail::exp_bits<from_t>() >= to_bits) {
                return -detail::exp2<from_t>(to_bits);
            } else {
                return from_limits::lowest();
            }
        }

        return 0.f;
    }

    template <typename to_t, typename from_t>
    constexpr from_t upper_bound() noexcept {
        using to_limits = std::numeric_limits<to_t>;
        using from_limits = std::numeric_limits<from_t>;

        static_assert(to_limits::is_integer);
        static_assert(detail::is_binary_radix<to_t>);

        constexpr int to_bits = to_limits::digits;

        if constexpr (detail::exp_bits<from_t>() >= to_bits) {
            return detail::exp2<from_t>(to_bits);
        } else {
            return from_limits::infinity;
        }
    }

    // @credits: https://github.com/e00E/cpp-clamp-cast/blob/master/clamp-cast.hpp
    template <typename to_t, typename from_t>
    constexpr to_t safe_cast(const from_t from) {
        if (util::is_nan<from_t>(from)) {
            return 0;
        }

        if (from < lower_bound<to_t, from_t>()) {
            return std::numeric_limits<to_t>::min();
        }

        if (from >= upper_bound<to_t, from_t>()) {
            return std::numeric_limits<to_t>::max();
        }

        return static_cast<to_t>(from);
    }
} // namespace util