#if lucy_major >= 0 and lucy_middle >= 0 and lucy_minor >= 1
#ifndef lucy_meta_remove_references
#define lucy_meta_remove_references

namespace Lucy::Meta
{
    namespace Detail
    {
        template<class T> class RemoveReferences
        {
        public:
            using Type = T;
        };

        template<class T> class RemoveReferences<T&>
        {
        public:
            using Type = T;
        };

        template<class T> class RemoveReferences<T&&>
        {
        public:
            using Type = T;
        };
    }

    template<class T> using RemoveReferences = Detail::RemoveReferences<T>::Type;
}

#endif
#endif