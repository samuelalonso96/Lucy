#if lucy_major >= 0 and lucy_middle >= 0 and lucy_minor >= 1
#ifndef lucy_meta_copy_constructible
#define lucy_meta_copy_constructible

namespace Lucy::Meta
{
    template<class T> concept CopyConstructible = __is_constructible(T, const T&);
}

#endif
#endif