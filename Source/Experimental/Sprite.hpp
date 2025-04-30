#if lucy_major >= 0 and lucy_middle >= 0 and lucy_minor >= 1
#ifndef lucy_engine_sprite
#define lucy_engine_sprite
#include "Texture.hpp"
#include "Rect.hpp"
#include "Vertex.hpp"
#include "../Core/Size.hpp"

namespace Lucy::Engine
{
    class [[nodiscard]] Sprite
    {
        Vertex vertices[6];
        
        float pos = 0.f;

        bool negative = false;
    public:
        Rect rect;

        void* texture, *quad;

        static constexpr Size num_vertices = 6uz;

        [[nodiscard]] static auto Create(const Texture& texture) noexcept -> Sprite;

        auto operator+=(const float position) noexcept -> Sprite&;

        auto Render() noexcept -> void;
    };
}

#endif
#endif