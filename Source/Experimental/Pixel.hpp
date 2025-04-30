#if lucy_major >= 0 and lucy_middle >= 0 and lucy_minor >= 1
#ifndef lucy_engine_pixel
#define lucy_engine_pixel

namespace Lucy::Engine
{
    enum class [[nodiscard]] Pixel : unsigned char
    {
        BGRA8Unorm_sRGB,
        RGBA8Unorm_sRGB
    };
}

#endif
#endif