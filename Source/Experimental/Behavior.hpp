#if lucy_major >= 0 and lucy_middle >= 0 and lucy_minor >= 1
#ifndef lucy_engine_behavior
#define lucy_engine_behavior
#include "../Meta/Void.hpp"

namespace Lucy::Engine
{
    namespace Detail
    {
        template<class Behavior, class... Behaviors> [[nodiscard]] consteval auto DoCheck() noexcept
        -> bool
        {
            const bool result = requires(Behavior& self)
            {
                {self.Start()} -> Meta::Void;
                {self.Update()} -> Meta::Void;
                {self.Finish()} -> Meta::Void;
            };
            if constexpr(sizeof...(Behaviors) > 0uz)
                return result and DoCheck<Behaviors...>();
            return result;
        }

        template<class... Behaviors> [[nodiscard]] consteval auto Check() noexcept -> bool
        {
            return DoCheck<Behaviors...>();
        }
    }

    template<class... Behaviors> concept Behavior = sizeof...(Behaviors) > 0uz and Check<Behaviors
    ...>();
}

#endif
#endif