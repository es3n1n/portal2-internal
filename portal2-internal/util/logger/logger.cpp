#include "logger.h"

namespace util {
    namespace logger {
        namespace _colors {
            void* m_console_handle = nullptr;

            bool ensure_handle() {
                if (!m_console_handle)
                    m_console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
                return static_cast<bool>(m_console_handle);
            }

            void apply(uint32_t clr) {
                if (!ensure_handle())
                    return;
                SetConsoleTextAttribute(m_console_handle, clr);
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
            AllocConsole();
            freopen_s(reinterpret_cast<FILE**>(stdin), "CONIN$", "r", stdin);
            freopen_s(reinterpret_cast<FILE**>(stdout), "CONOUT$", "w", stdout);
#endif
            // @todo: clear console
        }
    } // namespace logger
} // namespace util
