#include "hack.hpp"

#include "hooks/hooks.hpp"

#include <chrono>
#include <thread>

namespace hack {
    namespace bootstrap {
        namespace {
            DWORD __stdcall _initial_routine(HANDLE) {
                util::logger::startup();

                cfg::init();
                util::hooking::detour::init();
                portal::initial();
                hooks::setup();
                util::input::init();

                _handle_unload();

                _shutdown();
                return 1; // unreachable but whatever
            }
        } // namespace

        void handle_input() {
            if (!util::input::get(VK_DELETE).pressed())
                return;
            running = false;
            _watcher.notify_one();
        }

        bool startup(HANDLE dll_handle) {
            TRACE_FN;
            _dll_handle = dll_handle;
            CreateThread(nullptr, 0, LPTHREAD_START_ROUTINE(_initial_routine), 0, 0, nullptr);
            return true;
        }

        void _handle_unload() {
            std::mutex _mtx;
            std::unique_lock<std::mutex> thread_lock(_mtx);
            _watcher.wait(thread_lock, []() -> bool { return !running; });
            thread_lock.unlock();
        }

        void _shutdown() {
            TRACE_FN;
            hooks::unhook();
            util::input::deinit();
            if (menu::opened)
                util::game::unlock_cursor();
            FreeLibraryAndExitThread(static_cast<HMODULE>(_dll_handle), 0x1);
        }
    } // namespace bootstrap
} // namespace hack
