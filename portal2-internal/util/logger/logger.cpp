#include "logger.hpp"

namespace util {
    namespace logger {
        namespace _colors {
            void* m_console_handle = nullptr;

            bool ensure_handle() {
#ifndef IS_WIN
                return false;
#else
                if (!m_console_handle)
                    m_console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
                return static_cast<bool>(m_console_handle);
#endif
            }

            void apply(uint32_t clr) {
#ifndef IS_WIN
                return;
#else
                if (!ensure_handle())
                    return;
                SetConsoleTextAttribute(m_console_handle, clr);
#endif
            }

            void reset() {
                apply(static_cast<uint32_t>(e_level_color::level_color_none));
            }

            void colorify(uint32_t clr, std::function<void()> cb) {
                apply(clr);
                cb();
                reset();
            }
        } // namespace _colors

        void log(const char* prefix, e_level_color level, const char* message) {
            std::lock_guard<std::mutex> lock(_mtx);
            _colors::colorify(static_cast<uint32_t>(level), [prefix]() -> void { printf("%s >> ", prefix); });

            printf("%s\n", message);
        }

        void startup() {
#ifdef ALLOC_CONSOLE
    #ifndef IS_WIN
            return;
    #else
            AllocConsole();
    #endif
            freopen_s(reinterpret_cast<FILE**>(stdin), "CONIN$", "r", stdin);
            freopen_s(reinterpret_cast<FILE**>(stdout), "CONOUT$", "w", stdout);
#endif
            // @todo: clear console
        }
    } // namespace logger
} // namespace util
