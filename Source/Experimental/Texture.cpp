#include "Texture.hpp"

namespace Lucy::Engine
{
    [[nodiscard]] auto Texture::Create(const Formats::QOI& image, const Pixel target) noexcept ->
    Texture
    {
        Texture texture;
        texture.height = image.height;
        texture.width = image.width;
        texture.format = target;
        switch(target)
        {
            using enum Pixel;
            case BGRA8Unorm_sRGB:
                switch(image.format)
                {
                    case RGBA8Unorm_sRGB:
                    {
                        texture.pixels.reserve(image.pixels.size());
                        unsigned char mode = 0u, red, green;
                        for(const unsigned char channel : image.pixels)
                            switch(mode)
                            {
                                case 0u:
                                    ++mode;
                                    red = channel;
                                break;
                                case 1u:
                                    ++mode;
                                    green = channel;
                                break;
                                case 2u:
                                    ++mode;
                                    texture.pixels.emplace_back(channel);
                                    texture.pixels.emplace_back(green);
                                    texture.pixels.emplace_back(red);
                                break;
                                case 3u:
                                    mode = 0u;
                                    texture.pixels.emplace_back(channel);
                                break;
                            }
                    }
                    break;
                    default:
                    break;
                }
            break;
            default:
            break;
        }
        return texture;
    }
}