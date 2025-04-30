#if lucy_major >= 0 and lucy_middle >= 0 and lucy_minor >= 1
#ifndef lucy_engine_texture
#define lucy_engine_texture
#include "QOI.hpp"

namespace Lucy::Engine
{
    class [[nodiscard]] Texture
    {
    public:
        unsigned short width, height;

        Pixel format;

        std::vector<unsigned char> pixels;

        [[nodiscard]] static auto Create(const Formats::QOI& image, const Pixel target) noexcept ->
        Texture;
    };
}

#endif
#endif