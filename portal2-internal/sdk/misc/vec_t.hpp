#pragma once
#include <cmath>

struct vec2_t {
public:
    float x;
    float y;

    constexpr vec2_t(float x, float y): x(x), y(y) { }

    float length() const {
        return std::sqrt(x * x + y * y);
    }
};

struct vec3_t {
public:
    float x;
    float y;
    float z;

    constexpr vec3_t(float x = 0.f, float y = 0.f, float z = 0.f): x(x), y(y), z(z) { }

    float length() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    float length_2d() const {
        return std::sqrt(x * x + y * y);
    }

    bool operator==(vec3_t& rhs) {
        return std::abs(this->x - rhs.x) <= 0.01f && std::abs(this->y - rhs.y) <= 0.01f && std::abs(this->z - rhs.z) <= 0.01f;
    }
};

struct vec4_t {
public:
    float x;
    float y;
    float z;
    float w;

    constexpr vec4_t(float x, float y, float z, float w): x(x), y(y), z(z), w(w) { }
};