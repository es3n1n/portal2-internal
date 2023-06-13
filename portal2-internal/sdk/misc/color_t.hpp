#pragma once
#include <cmath>
#include <cstdint>

#include "hack/menu/imgui/imgui.h"
#include "sdk/misc/flt_range_t.hpp"
#include "util/cast/cast.hpp"

struct color_t {
    using channel_t = std::uint8_t;
    using channel_flt_t = flt_range_t;

    using channel_limit_t = std::numeric_limits<channel_t>;
    using channel_flt_limit_t = std::numeric_limits<channel_flt_t>;

public:
    constexpr color_t() = default;
    constexpr ~color_t() = default;

public:
    constexpr color_t(channel_t r, channel_t g, channel_t b, channel_t a = channel_limit_t::max()) noexcept: r(r), g(g), b(b), a(a) { }

    // clang-format off
    constexpr color_t(channel_flt_t r, channel_flt_t g, channel_flt_t b, channel_flt_t a = channel_flt_limit_t::max()) noexcept : 
        r(channel_t(r * channel_limit_t::max())), 
        g(channel_t(g * channel_limit_t::max())), 
        b(channel_t(b * channel_limit_t::max())),
        a(channel_t(a * channel_limit_t::max())) { }
    // clang-format on

public:
    [[nodiscard]] color_t blend(channel_t r_, channel_t g_, channel_t b_, flt_range_t progress) {
        return color_t(channel_t((r_ * progress) + (r * (channel_flt_limit_t::max() - progress))),
                       channel_t((g_ * progress) + (g * (channel_flt_limit_t::max() - progress))),
                       channel_t((b_ * progress) + (b * (channel_flt_limit_t::max() - progress))));
    }

    [[nodiscard]] std::int32_t get_hex() {
        union {
            struct {
#if IS_BIG_ENDIAN
                channel_t a, r, g, b;
#else
                channel_t b, g, r, a;
#endif
            };

            std::int32_t raw;
        } converter;

        //
        // @todo: @es3n1n: find more convinient way to forward all colors
        //
        // @note: @kehrazy: there is no way to iterate thru structs in c++23
        //
        converter.r = r;
        converter.g = g;
        converter.b = b;
        converter.a = a;

        return converter.raw;
    }

public:
    inline color_t& apply(channel_t r = channel_limit_t::max(), channel_t g = channel_limit_t::max(), channel_t b = channel_limit_t::max(),
                          channel_t a = channel_limit_t::max()) {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;

        return *this;
    }

    inline color_t& apply(channel_flt_t r = channel_flt_limit_t::max(), channel_flt_t g = channel_flt_limit_t::max(),
                          channel_flt_t b = channel_flt_limit_t::max(), channel_flt_t a = channel_flt_limit_t::max()) {
        return apply(static_cast<channel_t>(r * channel_limit_t::max()), static_cast<channel_t>(g * channel_limit_t::max()),
                     static_cast<channel_t>(b * channel_limit_t::max()), static_cast<channel_t>(a * channel_limit_t::max()));
    }

    inline color_t& apply(color_t src) {
        return apply(src.r, src.g, src.b, src.a);
    }

    inline color_t& replace_a(channel_t a) {
        this->a = a;
        return *this;
    }

    inline color_t& replace_a(channel_flt_t a) {
        this->a = static_cast<channel_t>(a * channel_limit_t::max());
        return *this;
    }

public:
    // @credits: https://github.com/znsoftm/xtd/blob/master/src/xtd.drawing/src/xtd/drawing/color.cpp#L186
    [[nodiscard]] static color_t from_hsb(flt_range_t hue, flt_range_t saturation, flt_range_t brightness) {
        if (!saturation)
            return color_t(brightness, brightness, brightness, util::safe_cast<channel_flt_t>(1.f));

        hue = std::fabsf(hue - 1.0f) <= 0.001f ? 0.f : hue * 6.0f;

        constexpr float f = hue - std::trunc(hue);
        constexpr float p = brightness * (1.f - saturation);
        constexpr float q = brightness * (1.f - (saturation * f));
        constexpr float t = brightness * (1.f - (saturation * (1.f - f)));

        constexpr channel_t chan_max = channel_limit_t::max();

        switch (util::safe_cast<int>(std::trunc(hue))) {
        case 0:
            return color_t(util::safe_cast<channel_t>(brightness * chan_max), util::safe_cast<channel_t>(t * chan_max),
                           util::safe_cast<channel_t>(p * chan_max));
        case 1:
            return color_t(util::safe_cast<channel_t>(q * chan_max), util::safe_cast<channel_t>(brightness * chan_max),
                           util::safe_cast<channel_t>(p * chan_max));
        case 2:
            return color_t(util::safe_cast<channel_t>(p * chan_max), util::safe_cast<channel_t>(brightness * chan_max),
                           util::safe_cast<channel_t>(t * chan_max));
        case 3:
            return color_t(util::safe_cast<channel_t>(p * chan_max), util::safe_cast<channel_t>(q * chan_max),
                           util::safe_cast<channel_t>(brightness * chan_max));
        case 4:
            return color_t(util::safe_cast<channel_t>(t * chan_max), util::safe_cast<channel_t>(p * chan_max),
                           util::safe_cast<channel_t>(brightness * chan_max));
        default:
            return color_t(util::safe_cast<channel_t>(brightness * chan_max), util::safe_cast<channel_t>(p * chan_max),
                           util::safe_cast<channel_t>(q * chan_max));
        }
    }

public:
    channel_t r = 0;
    channel_t g = 0;
    channel_t b = 0;
    channel_t a = 255;

    struct {
        void set(flt_range_t val) {
            value = val;
        }

        void reset() {
            value = limits_t::min();
        }

        void increment() {
            constexpr float coef = 0.1f;

            value = xstd::clamp<decltype(value)>((value >= limits_t::max() ? limits_t::min() : value) + (coef * ImGui::GetIO().DeltaTime));
        }

    public:
        bool enabled = false;
        flt_range_t value = 0.f;

    public:
        using limits_t = std::numeric_limits<decltype(value)>;
    } rainbow;

public:
#define DECL_COLOR(name, r, g, b, a) \
    static constexpr color_t name() { return color_t(r, g, b, a); }

    DECL_COLOR(black, 0, 0, 0, 255);
    DECL_COLOR(white, 0, 0, 0, 255);

#undef DECL_COLOR
};

static_assert(!std::is_same_v<color_t::channel_t, color_t::channel_flt_t> && xstd::is_floating_point_v<color_t::channel_flt_t> &&
                  !xstd::is_floating_point_v<color_t::channel_t>,
              "please adjust color channel types");
