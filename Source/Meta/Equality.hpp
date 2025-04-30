#if lucy_major >= 0 and lucy_middle >= 0 and lucy_minor >= 1
#ifndef lucy_meta_equality
#define lucy_meta_equality
#include "Same.hpp"
#include "../Core/Forward.hpp"

namespace Lucy::Meta
{
    template<class T, class Rhs = T> concept Equality = requires(T& t, Rhs rhs)
    {
        {t == lucy_forward(rhs)} -> Same<bool>;
    };
}

#endif
#endif