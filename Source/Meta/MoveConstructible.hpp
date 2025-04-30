#if lucy_major >= 0 and lucy_middle >= 0 and lucy_minor >= 1
#ifndef lucy_meta_move_constructible
#define lucy_meta_move_constructible
#include "RemoveLvalueReference.hpp"

namespace Lucy::Meta
{
    template<class T> concept MoveConstructible = __is_constructible(T, RemoveLvalueReference<T>&&)
    ;
}

#endif
#endif