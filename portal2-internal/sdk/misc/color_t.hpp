#pragma once
#include <cmath>
#include <cstdint>

struct color_t {
    std::uint8_t r = 0, g = 0, b = 0, a = 255;

    bool rainbow = false;
    float rainbow_value = 0.f;

    color_t() = default;
    ~color_t() = default;

    constexpr color_t(std::int32_t r, std::int32_t g, std::int32_t b, std::int32_t a = 255) noexcept: r(r), g(g), b(b), a(a) { }
    constexpr color_t(float r, float g, float b, float a = 1.f) noexcept
        : r(std::int32_t(r * 255.f)), g(std::int32_t(g * 255.f)), b(std::int32_t(b * 255.f)), a(std::int32_t(a * 255.f)) { }

    color_t blend(std::int32_t r_, std::int32_t g_, std::int32_t b_, float progress) {
        return color_t(static_cast<unsigned char>((r_ * progress) + (r * (1.f - progress))),
                       static_cast<unsigned char>((g_ * progress) + (g * (1.f - progress))),
                       static_cast<unsigned char>((b_ * progress) + (b * (1.f - progress))));
    }

    unsigned long get_hex() {
        return (unsigned long)((((int)this->a & 0xff) << 0x18) | (((int)this->r & 0xff) << 0x10) | (((int)this->g & 0xff) << 0x8) | ((int)this->b & 0xff));
    }

    void apply(std::int32_t r, std::int32_t g, std::int32_t b, std::int32_t a) {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }

    void apply(float r, float g, float b, float a) {
        this->r = static_cast<std::int32_t>(r * 255.f);
        this->g = static_cast<std::int32_t>(g * 255.f);
        this->b = static_cast<std::int32_t>(b * 255.f);
        this->a = static_cast<std::int32_t>(a * 255.f);
    }

    static color_t from_hsb(float hue, float saturation, float brightness) {
        float h = std::fabsf(hue - 1.0f) <= 0.001f ? 0.f : hue * 6.0f;
        float f = h - (int)h;
        float p = brightness * (1.0f - saturation);
        float q = brightness * (1.0f - saturation * f);
        float t = brightness * (1.0f - (saturation * (1.0f - f)));

        if (h < 1) {
            return color_t((unsigned char)(brightness * 255), (unsigned char)(t * 255), (unsigned char)(p * 255));
        } else if (h < 2) {
            return color_t((unsigned char)(q * 255), (unsigned char)(brightness * 255), (unsigned char)(p * 255));
        } else if (h < 3) {
            return color_t((unsigned char)(p * 255), (unsigned char)(brightness * 255), (unsigned char)(t * 255));
        } else if (h < 4) {
            return color_t((unsigned char)(p * 255), (unsigned char)(q * 255), (unsigned char)(brightness * 255));
        } else if (h < 5) {
            return color_t((unsigned char)(t * 255), (unsigned char)(p * 255), (unsigned char)(brightness * 255));
        } else {
            return color_t((unsigned char)(brightness * 255), (unsigned char)(p * 255), (unsigned char)(q * 255));
        }
    }
};
