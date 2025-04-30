#include <Experimental/Game.hpp>
#include <Experimental/Sprite.hpp>
#include <Experimental/Shader.hpp>
#include <Experimental/File.hpp>

using namespace Lucy::IO::File;
using namespace Lucy::Engine;
using namespace Lucy::Formats;

namespace lucy_game
{
    Shader shader;
    Sprite school, wisteria, hoshino;

    auto Start() noexcept -> void
    {
        shader = Shader::Create(
            Kernel::Create("vertexShader", KernelKind::Vertex),
            Kernel::Create("samplingShader", KernelKind::Fragment)
        );
        school = Sprite::Create(
            Texture::Create(
                PNG(Read("School.qoi")),
                Pixel::BGRA8Unorm_sRGB
            )
        );
        wisteria = Sprite::Create(
            Texture::Create(
                PNG(Read("WisteriaHappy.qoi")),
                Pixel::BGRA8Unorm_sRGB
            )
        );
        hoshino = Sprite::Create(
            Texture::Create(
                PNG(Read("HoshinoSmile.qoi")),
                Pixel::BGRA8Unorm_sRGB
            )
        );
    }

    auto Update() noexcept -> void
    {
        shader.Render();
        school.Render();
        wisteria.Render();
        hoshino.Render();
        wisteria += .01f;
    }

    auto Finish() noexcept -> void
    {}
}