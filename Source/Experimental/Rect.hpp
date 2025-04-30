#if lucy_major >= 0 and lucy_middle >= 0 and lucy_minor >= 1
#ifndef lucy_engine_rect
#define lucy_engine_rect

namespace Lucy::Engine
{
    class [[nodiscard]] Rect
    {
    public:
        float x = 0.f, y = 0.f, width = 0.f, height = 0.f;
    };
}

#endif
#endif