#include "Shader.hpp"
#include "Renderer.hpp"
#include <Metal/Metal.h>

namespace Lucy::Engine
{
    [[nodiscard]] auto Kernel::Create(const char* name, const KernelKind kind) noexcept -> Kernel
    {
        Kernel kernel;
        kernel.kind = kind;
        kernel.function = [static_cast<id<MTLLibrary>>(Graphics::renderer.Library()) newFunctionWithName: [NSString stringWithUTF8String: name]];
        return kernel;
    }

    [[nodiscard]] auto Shader::Create(const Kernel &vertex, const Kernel &fragment) noexcept -> Shader
    {
        MTLRenderPipelineDescriptor *pipelineStateDescriptor = [[MTLRenderPipelineDescriptor alloc] init];
        pipelineStateDescriptor.label = @"Texturing Pipeline";
        pipelineStateDescriptor.vertexFunction = static_cast<id<MTLFunction>>(vertex.function);
        pipelineStateDescriptor.fragmentFunction = static_cast<id<MTLFunction>>(fragment.function);
        pipelineStateDescriptor.colorAttachments[0].pixelFormat = MTLPixelFormatBGRA8Unorm;
        pipelineStateDescriptor.alphaToCoverageEnabled = true;
        Shader shader;
        shader.pso = [static_cast<id<MTLDevice>>(Graphics::renderer.Device()) newRenderPipelineStateWithDescriptor:pipelineStateDescriptor error:nil];
        return shader;
    }

    auto Shader::Render() noexcept -> void
    {
        [static_cast<id<MTLRenderCommandEncoder>>(Graphics::renderer.Encoder()) setRenderPipelineState: static_cast<id<MTLRenderPipelineState>>(pso)];
    }
}