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

namespace platform {
    constexpr bool is_win = IS_WIN;
    constexpr bool is_win32 = IS_WIN32;
    constexpr bool is_win64 = IS_WIN64;
    constexpr bool is_linux = IS_LINUX;
    constexpr bool is_apple = IS_APPLE;
} // namespace platform
