#if lucy_major >= 0 and lucy_middle >= 0 and lucy_minor >= 1
#ifndef lucy_meta_inequality
#define lucy_meta_inequality
#include "Same.hpp"
#include "../Core/Forward.hpp"

namespace Lucy::Meta
{
    template<class T, class Rhs = T> concept Inequality = requires(T& t, Rhs rhs)
    {
        {t not_eq lucy_forward(rhs)} -> Same<bool>;
    };
}

#endif
#endif