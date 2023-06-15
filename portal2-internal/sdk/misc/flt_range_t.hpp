#pragma once
#include <algorithm>
#include <cstdint>
#include <numeric>

struct flt_range_t {
public:
    constexpr flt_range_t() = default;
    constexpr ~flt_range_t() = default;

public:
    constexpr flt_range_t(float value): value(value) { }

public:
    constexpr operator float() {
        return value;
    }

public:
    float value = 0.f;
};

//
// @todo: @es3n1n: implement other functions, not that i care about em anyway
//
namespace std {
    template <>
    class numeric_limits<flt_range_t> {
    public:
        [[nodiscard]] static constexpr flt_range_t(min)() noexcept {
            return 0.f;
        }

        [[nodiscard]] static constexpr flt_range_t(max)() noexcept {
            return 1.f;
        }
    };
} // namespace std

namespace xstd {
    /*
    template <class _Ty, class... _Types>
    _INLINE_VAR constexpr bool _Is_any_of_v = // true if and only if _Ty is in _Types
                disjunction_v<is_same<_Ty, _Types>...>;
    */
    template <class _Ty, class... _Types>
    inline constexpr bool is_any_of_v = std::disjunction_v<std::is_same<_Ty, _Types>...>;

    template <class _Ty>
    inline constexpr bool is_floating_point_v = is_any_of_v<std::remove_cv_t<_Ty>, float, double, long double, flt_range_t>;

    template <class _Ty>
    inline constexpr _Ty clamp(_Ty value) {
        return value < std::numeric_limits<_Ty>::min() ? std::numeric_limits<_Ty>::min() :
               value > std::numeric_limits<_Ty>::max() ? std::numeric_limits<_Ty>::max() :
                                                         value;
    }
} // namespace xstd
