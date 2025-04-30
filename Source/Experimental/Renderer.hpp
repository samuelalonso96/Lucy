#if lucy_major >= 0 and lucy_middle >= 0 and lucy_minor >= 1
#ifndef lucy_graphics_renderer
#define lucy_graphics_renderer
#include <array>

namespace Lucy::Graphics
{
    namespace Detail
    {
        extern bool RendererRunning;

        extern bool RendererUpdating;
    }

    enum class [[nodiscard]] FramebufferState : unsigned char
    {
        Uninit,
        Busy,
        Free
    };

    class [[nodiscard]] Framebuffer
    {
    public:
        FramebufferState state;

        void* buffer;

        void* encoder;
    };

    class [[nodiscard]] Renderer
    {
        #ifdef lucy_mac
        void* m_device;

        void* m_display;

        void* m_library;

        void* m_queue;

        void* m_drawable;

        Framebuffer* m_actual;

        std::array<Framebuffer, 512uz> m_fbo;
        #endif
    public:
        auto Init(void* delegate) noexcept -> void;

        auto Update(void* update) noexcept -> void;

        auto Dispatch(void* update) noexcept -> void;

        [[nodiscard]] auto Device() noexcept -> void*;

        [[nodiscard]] auto Display() noexcept -> void*;

        [[nodiscard]] auto Library() noexcept -> void*;

        [[nodiscard]] auto Queue() noexcept -> void*;

        [[nodiscard]] auto Encoder() noexcept -> void*;

        [[nodiscard]] auto Drawable() noexcept -> void*;
    };

    extern Renderer renderer;
}

#endif
#endif