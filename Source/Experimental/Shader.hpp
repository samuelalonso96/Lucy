#if lucy_major >= 0 and lucy_middle >= 0 and lucy_minor >= 1
#ifndef lucy_engine_shader
#define lucy_engine_shader

namespace Lucy::Engine
{
    enum class [[nodiscard]] KernelKind : unsigned char
    {
        Vertex,
        Fragment
    };

    class [[nodiscard]] Kernel
    {
    public:
        KernelKind kind;

        void* function;

        [[nodiscard]] static auto Create(const char* name, const KernelKind kind) noexcept -> Kernel;
    };

    class [[nodiscard]] Shader
    {
    public:
        void* pso;

        [[nodiscard]] static auto Create(const Kernel& vertex, const Kernel& fragment) noexcept -> Shader;

        auto Render() noexcept -> void;
    };
}

#endif
#endif