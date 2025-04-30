#if lucy_major >= 0 and lucy_middle >= 0 and lucy_minor >= 1
#ifndef lucy_meta_trivially_copy_constructible
#define lucy_meta_trivially_copy_constructible

namespace Lucy::Meta
{
    template<class T> concept TriviallyCopyConstructible = __is_trivially_constructible(T, const T&
    );
}

#endif
#endif