#if lucy_major >= 0 and lucy_middle >= 0 and lucy_minor >= 1
#ifndef lucy_meta_move_assignable
#define lucy_meta_move_assignable
#include "RemoveLvalueReference.hpp"

namespace Lucy::Meta
{
    template<class T> concept MoveAssignable = __is_assignable(T, RemoveLvalueReference<T>&&);
}

#endif
#endif