#if lucy_major >= 0 and lucy_middle >= 0 and lucy_minor >= 1
#ifndef lucy_meta_remove_extents
#define lucy_meta_remove_extents
#include "../Core/Size.hpp"

namespace Lucy::Meta
{
    namespace Detail
    {
        template<class T> class RemoveExtents
        {
        public:
            using Type = T;
        };

        template<class T> class RemoveExtents<T[]>
        {
        public:
            using Type = RemoveExtents<T>::Type;
        };

        template<class T, Size size> class RemoveExtents<T[size]>
        {
        public:
            using Type = RemoveExtents<T>::Type;
        };
    }

    template<class T> using RemoveExtents = Detail::RemoveExtents<T>::Type;
}

#endif
#endif