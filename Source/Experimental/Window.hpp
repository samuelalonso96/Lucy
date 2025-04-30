#if lucy_major >= 0 and lucy_middle >= 0 and lucy_minor >= 1
#ifndef lucy_ui_window
#define lucy_ui_window

namespace Lucy::UI
{
    namespace Detail
    {
        extern bool WindowLoaded;
    }

    class [[nodiscard]] Window
    {
        #ifdef lucy_mac
        void* m_window;
        #endif
    public:
        auto Init() noexcept -> void;

        [[nodiscard]] auto Layer() noexcept -> void*;

        auto Title(const char* title) noexcept -> void;
    };

    extern Window window;
}

#endif
#endif