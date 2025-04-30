#include "Sprite.hpp"
#include "Renderer.hpp"
#include "../../Shader/Types.h"
#include <Metal/Metal.h>

namespace Lucy::Engine
{
    [[nodiscard]] auto Sprite::Create(const Texture& texture) noexcept -> Sprite
    {
        Sprite sprite;
        sprite.rect.x = -texture.width / 2.f;
        sprite.rect.y = -texture.height / 2.f;
        sprite.rect.width = texture.width;
        sprite.rect.height = texture.height;
        MTLTextureDescriptor* textureDescriptor = [[MTLTextureDescriptor alloc] init];
        textureDescriptor.pixelFormat = MTLPixelFormatBGRA8Unorm;
        textureDescriptor.width = texture.width;
        textureDescriptor.height = texture.height;
        id<MTLTexture> ttr = [static_cast<id<MTLDevice>>(Graphics::renderer.Device()) newTextureWithDescriptor: textureDescriptor];
        sprite.texture = ttr;
        [ttr replaceRegion: MTLRegion{{ 0, 0, 0 }, {texture.width, texture.height, 1}} mipmapLevel:0 withBytes: texture.pixels.data() bytesPerRow: texture.width * 4];
        const float px = sprite.rect.x + texture.width, py = sprite.rect.y + texture.height, nx = -px, ny = -py;
        sprite.vertices[0] = { px, ny, 1.f, 1.f };
        sprite.vertices[1] = { nx, ny, 0.f, 1.f };
        sprite.vertices[2] = { nx, py, 0.f, 0.f };
        sprite.vertices[3] = { px, ny, 1.f, 1.f };
        sprite.vertices[4] = { nx, py, 0.f, 0.f };
        sprite.vertices[5] = { px, py, 1.f, 0.f };
        sprite.quad = [static_cast<id<MTLDevice>>(Graphics::renderer.Device()) newBufferWithBytes: sprite.vertices length:sizeof(vertices) options:MTLResourceStorageModeShared];
        return sprite;
    }

    auto Sprite::operator+=(const float position) noexcept -> Sprite&
    {
        if(pos > .5f)
            negative = true;
        else if(pos < -.5f)
            negative = false;
        pos += negative ? -position : position;
        return *this;
    }

    auto Sprite::Render() noexcept -> void
    {
        id<MTLRenderCommandEncoder> encoder = static_cast<id<MTLRenderCommandEncoder>>(Graphics::renderer.Encoder());
        [encoder setVertexBuffer:static_cast<id<MTLBuffer>>(quad) offset:0 atIndex: AAPLVertexInputIndexVertices];
        [encoder setVertexBytes:&pos length:4 atIndex:2];
        [encoder setFragmentTexture: static_cast<id<MTLTexture>>(texture) atIndex:AAPLTextureIndexBaseColor];
        [encoder drawPrimitives:MTLPrimitiveTypeTriangle vertexStart:0 vertexCount:num_vertices];
    }
}