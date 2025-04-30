#if lucy_major >= 0 and lucy_middle >= 0 and lucy_minor >= 1
#ifdef lucy_debug
#include "Debugger.hpp"
#include "Renderer.hpp"

namespace Lucy::Engine
{
    Debugger debugger;

    [[nodiscard]] auto Debugger::Create() noexcept -> Debugger
    {
        Debugger debugger;
        
        return debugger;
    }
}

#endif
#endif