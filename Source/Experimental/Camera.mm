#include "Camera.hpp"
#include "Renderer.hpp"
#include "../../Shader/Types.h"
#include <Metal/Metal.h>
#include <QuartzCore/QuartzCore.h>

namespace Lucy::Engine
{
    Camera main;

    [[nodiscard]] auto Camera::Create() noexcept -> Camera
    {
        Camera camera;
        camera.far = 1.;
        camera.near = -1.;
        return camera;
    }

    auto Camera::Render() noexcept -> void
    {
        if(Graphics::Detail::RendererUpdating)
        {
            MTLViewport viewport;
            id<CAMetalDrawable> drawable = static_cast<id<CAMetalDrawable>>(Graphics::renderer.Drawable());
            viewport.width = drawable.texture.width;
            viewport.height = drawable.texture.height;
            viewport.originX = 0.;
            viewport.originY = 0.;
            viewport.zfar = far;
            viewport.znear = near;
            const vector_uint2 vs{static_cast<unsigned int>(viewport.width), static_cast<unsigned int>(viewport.height)};
            id<MTLRenderCommandEncoder> encoder = static_cast<id<MTLRenderCommandEncoder>>(Graphics::renderer.Encoder());
            [encoder setViewport: viewport];
            [encoder setVertexBytes: &vs length: sizeof(vs) atIndex: AAPLVertexInputIndexViewportSize];
        }
    }
}