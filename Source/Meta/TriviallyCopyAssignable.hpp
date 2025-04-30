#if lucy_major >= 0 and lucy_middle >= 0 and lucy_minor >= 1
#ifndef lucy_meta_trivially_copy_assignable
#define lucy_meta_trivially_copy_assignable

namespace Lucy::Meta
{
    template<class T> concept TriviallyCopyAssignable = __is_trivially_assignable(T, const T&);
}

#endif
#endif