#if lucy_major >= 0 and lucy_middle >= 0 and lucy_minor >= 1
#ifndef lucy_meta_trivially_destructible
#define lucy_meta_trivially_destructible
#ifndef __clang__
#include "Destructible.hpp"
#endif

namespace Lucy::Meta
{
    template<class T> concept TriviallyDestructible =
    #ifdef __clang__
    __is_trivially_destructible
    #else
    Destructible<T> and __has_trivial_destructor
    #endif
    (T);
}

#endif
#endif