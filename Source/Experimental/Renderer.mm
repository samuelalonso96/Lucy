#include "../Core/Abort.hpp"
#include "Renderer.hpp"
#include "Window.hpp"
#include "../../Shader/Types.h"
#include <Metal/Metal.h>
#include <QuartzCore/QuartzCore.h>

namespace Lucy::Graphics
{
    namespace Detail
    {
        bool RendererRunning = false;

        bool RendererUpdating = false;
    }

    Renderer renderer;

    auto Renderer::Init(void* delegate) noexcept -> void
    {
        if(not Detail::RendererRunning)
        {
            Detail::RendererRunning = true;
            id<MTLDevice> v_device = MTLCreateSystemDefaultDevice();
            if([v_device supportsFamily: MTLGPUFamilyMetal3])
            {
                m_device = v_device;
                m_queue = [v_device newCommandQueue];
                m_library = [v_device newDefaultLibrary];
                CAMetalLayer* v_layer = static_cast<CAMetalLayer*>(UI::window.Layer());
                v_layer.device = v_device;
                v_layer.maximumDrawableCount = 2ull;
                v_layer.pixelFormat = MTLPixelFormatBGRA8Unorm;
                v_layer.framebufferOnly = YES;
                CAMetalDisplayLink* v_display = [[CAMetalDisplayLink alloc] initWithMetalLayer: v_layer];
                v_display.delegate = static_cast<id<CAMetalDisplayLinkDelegate>>(delegate);
                m_display = v_display;
            }
            else
                Abort();
        }
    }

    auto Renderer::Update(void* update) noexcept -> void
    {
        if(Detail::RendererUpdating)
        {
            m_drawable = update;
            id<CAMetalDrawable> v_drawable = static_cast<id<CAMetalDrawable>>(update);
            Framebuffer* fbo;
            nya: for(Framebuffer& o_fbo : m_fbo)
            {
                fbo = &o_fbo;
                switch(fbo->state)
                {
                    case FramebufferState::Uninit:
                    case FramebufferState::Free:
                    {
                        fbo->state = FramebufferState::Busy;
                        MTLRenderPassDescriptor* pass = [MTLRenderPassDescriptor renderPassDescriptor];
                        pass.colorAttachments[0].texture = v_drawable.texture;
                        pass.colorAttachments[0].loadAction = MTLLoadActionClear;
                        static constexpr MTLClearColor clearColor{0., 0., 0., 1.};
                        pass.colorAttachments[0].clearColor = clearColor;
                        id<MTLCommandBuffer> commandBuffer = [static_cast<id<MTLCommandQueue>>(m_queue) commandBuffer];
                        fbo->buffer = commandBuffer;
                        fbo->encoder = [commandBuffer renderCommandEncoderWithDescriptor: pass];
                        [commandBuffer addCompletedHandler:^([[maybe_unused]] id<MTLCommandBuffer> _)
                        {
                            fbo->state = FramebufferState::Free;
                        }];
                    }
                    goto meow;
                    case FramebufferState::Busy:
                    continue;
                }
            }
            goto nya;
            meow:;
            m_actual = fbo;
        }
    }

    auto Renderer::Dispatch(void* update) noexcept -> void
    {
        if(Detail::RendererUpdating)
        {
            [static_cast<id<MTLRenderCommandEncoder>>(m_actual->encoder) endEncoding];
            id<MTLCommandBuffer> commandBuffer = static_cast<id<MTLCommandBuffer>>(m_actual->buffer);
            [commandBuffer presentDrawable: static_cast<id<MTLDrawable>>(update)];
            [commandBuffer commit];
        }
    }

    [[nodiscard]] auto Renderer::Device() noexcept -> void*
    {
        return m_device;
    }

    [[nodiscard]] auto Renderer::Display() noexcept -> void*
    {
        return m_display;
    }

    [[nodiscard]] auto Renderer::Library() noexcept -> void*
    {
        return m_library;
    }

    [[nodiscard]] auto Renderer::Queue() noexcept -> void*
    {
        return m_queue;
    }

    [[nodiscard]] auto Renderer::Encoder() noexcept -> void*
    {
        return m_actual->encoder;
    }

    [[nodiscard]] auto Renderer::Drawable() noexcept -> void*
    {
        return m_drawable;
    }
}