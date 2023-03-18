#pragma once
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
};

struct vec4_t {
public:
    float x;
    float y;
    float z;
    float w;
};