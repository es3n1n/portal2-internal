#pragma once
#include <cmath>
#include <intrin.h>

struct vec2_t {
public:
    float x;
    float y;

    float length() const {
        return _mm_cvtss_f32(_mm_sqrt_ss(_mm_set_ss(x * x + y * y)));
    }
};

struct vec3_t {
public:
    float x;
    float y;
    float z;

    float length() const {
        return _mm_cvtss_f32(_mm_sqrt_ss(_mm_set_ss(x * x + y * y + z * z)));
    }

    float length_2d() const {
        return _mm_cvtss_f32(_mm_sqrt_ss(_mm_set_ss(x * x + y * y)));
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
};