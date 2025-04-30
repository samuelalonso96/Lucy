#if lucy_major >= 0 and lucy_middle >= 0 and lucy_minor >= 1
#ifndef lucy_meta_constructible
#define lucy_meta_constructible

namespace Lucy::Meta
{
    template<class T, class... Arguments> concept Constructible = __is_constructible(T, Arguments...);
}

#endif
#endif