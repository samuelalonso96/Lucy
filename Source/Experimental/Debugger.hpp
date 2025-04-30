#if lucy_major >= 0 and lucy_middle >= 0 and lucy_minor >= 1
#ifdef lucy_debug
#ifndef lucy_engine_debugger
#define lucy_engine_debugger

namespace Lucy::Engine
{
    class [[nodiscard]] Debugger
    {
        
    public:
        [[nodiscard]] static auto Create() noexcept -> Debugger;
    };

    extern Debugger debugger;
}

#endif
#endif
#endif