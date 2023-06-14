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
template <>
class std::numeric_limits<flt_range_t> : public _Num_float_base {
public:
    _NODISCARD static constexpr flt_range_t(min)() noexcept {
        return 0.f;
    }

    _NODISCARD static constexpr flt_range_t(max)() noexcept {
        return 1.f;
    }
};

namespace xstd {
    template <class _Ty>
    _INLINE_VAR constexpr bool is_floating_point_v = std::_Is_any_of_v<std::remove_cv_t<_Ty>, float, double, long double, flt_range_t>;

    template <class _Ty>
    inline constexpr _Ty clamp(_Ty value) {
        return value < std::numeric_limits<_Ty>::min() ? std::numeric_limits<_Ty>::min() :
               value > std::numeric_limits<_Ty>::max() ? std::numeric_limits<_Ty>::max() :
                                                         value;
    }
} // namespace xstd
