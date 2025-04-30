#if lucy_major >= 0 and lucy_middle >= 0 and lucy_minor >= 1
#ifndef lucy_engine_camera
#define lucy_engine_camera

namespace Lucy::Engine
{
    class [[nodiscard]] Camera
    {
    public:
        double far, near;

        [[nodiscard]] static auto Create() noexcept -> Camera;

        auto Render() noexcept -> void;
    };

    extern Camera main;
}

#endif
#endif