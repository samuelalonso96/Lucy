#if lucy_major >= 0 and lucy_middle >= 0 and lucy_minor >= 1
#ifndef lucy_meta_copy_assignable
#define lucy_meta_copy_assignable

namespace Lucy::Meta
{
    template<class T> concept CopyAssignable = __is_assignable(T, const T&);
}

#endif
#endif