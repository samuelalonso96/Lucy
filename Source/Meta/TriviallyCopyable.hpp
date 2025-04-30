#if lucy_major >= 0 and lucy_middle >= 0 and lucy_minor >= 1
#ifndef lucy_meta_trivially_copyable
#define lucy_meta_trivially_copyable

namespace Lucy::Meta
{
    template<class T> concept TriviallyCopyable = __is_trivially_copyable(T);
}

#endif
#endif