#if lucy_major >= 0 and lucy_middle >= 0 and lucy_minor >= 1
#ifndef lucy_meta_destructible
#define lucy_meta_destructible
#include "Void.hpp"
#include "RemoveExtents.hpp"
#include "RemoveReferences.hpp"

namespace Lucy::Meta
{
    namespace Detail
    {
        template<class T> class Destructible
        {
        public:
            static consteval bool Value() noexcept
            {
                using U = ::Lucy::Meta::RemoveExtents<::Lucy::Meta::RemoveReferences<T>>;
                return requires(U u)
                {
                    u.~U();
                };
            }
        };
    }

    template<class T> concept Destructible = not Void<T> and Detail::Destructible<T>::Value();
}

#endif
#endif