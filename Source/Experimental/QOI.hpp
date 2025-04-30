#if lucy_major >= 0 and lucy_middle >= 0 and lucy_minor >= 1
#ifndef lucy_formats_qoi
#define lucy_formats_qoi
#include <vector>
#include "Pixel.hpp"

namespace Lucy::Formats
{
    class [[nodiscard]] QOI
    {
    public:
        std::vector<unsigned char> pixels;

        unsigned short width, height;

        bool transparency, srgb;

        Engine::Pixel format = Engine::Pixel::RGBA8Unorm_sRGB;

        QOI(const std::vector<unsigned char>& content) noexcept;
    };

    using PNG = QOI;
}

#endif
#endif