#pragma once
#include "cfg/cfg.hpp"
#include "features/features.hpp"
#include "hooks/hooks.hpp"
#include "menu/menu.hpp"
#include "sdk/portal.hpp"
#include "util/util.hpp"
#include <condition_variable>

namespace hack::bootstrap {
    inline std::condition_variable _watcher;
    inline HANDLE _dll_handle;
    inline bool running = true;

    bool startup(HANDLE handle);
    void handle_input();

    void _handle_unload();
    void _shutdown();
} // namespace hack::bootstrap
