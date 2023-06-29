#pragma once

#if defined(_WIN32)
    #define IS_WIN true
    #define IS_WIN32 true
    #define IS_WIN64 false
    #define IS_LINUX false
    #define IS_APPLE false
#elif defined(_WIN64)
    #define IS_WIN true
    #define IS_WIN32 false
    #define IS_WIN64 true
    #define IS_LINUX false
    #define IS_APPLE false
#elif defined(__linux__)
    #define IS_WIN false
    #define IS_WIN32 false
    #define IS_WIN64 false
    #define IS_LINUX true
    #define IS_APPLE false
#elif defined(__APPLE__)
    #define IS_WIN false
    #define IS_WIN32 false
    #define IS_WIN64 false
    #define IS_LINUX false
    #define IS_APPLE true
#endif

#if defined(__GNUC__)
    #define IS_GCC true
    #define IS_CLANG false
    #define IS_MSVC false
#elif defined(__clang__)
    #define IS_GCC false
    #define IS_CLANG true
    #define IS_MSVC false
#elif defined(_MSC_VER)
    #define IS_GCC false
    #define IS_CLANG false
    #define IS_MSVC true
#endif

namespace platform {
    constexpr bool is_win = IS_WIN;
    constexpr bool is_win32 = IS_WIN32;
    constexpr bool is_win64 = IS_WIN64;
    constexpr bool is_linux = IS_LINUX;
    constexpr bool is_apple = IS_APPLE;

    constexpr bool is_gcc = IS_GCC;
    constexpr bool is_clang = IS_CLANG;
    constexpr bool is_msvc = IS_MSVC;
} // namespace platform


//
// @note: @es3n1n: this is needed because on gcc we'll get some warnings
// since `[[maybe_unused]]` attribute is getting ignored on a member of
// a class or struct
//
#if IS_GCC
#define MAYBE_UNUSED_PAD
#else
#define MAYBE_UNUSED_PAD [[maybe_unused]]
#endif

