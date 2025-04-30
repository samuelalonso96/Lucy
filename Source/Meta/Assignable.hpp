#if lucy_major >= 0 and lucy_middle >= 0 and lucy_minor >= 1
#ifndef lucy_meta_assignable
#define lucy_meta_assignable
#include "Same.hpp"

namespace Lucy::Meta
{
    template<class T, class Rhs = T> concept Assignable = requires(T& t, Rhs rhs)
    {
        {t = lucy_forward(rhs)} -> Same<T&>;
    };
}

#endif
#endif