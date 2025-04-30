#if lucy_major >= 0 and lucy_middle >= 0 and lucy_minor >= 1
#ifndef lucy_meta_remove_lvalue_reference
#define lucy_meta_remove_lvalue_reference

namespace Lucy::Meta
{
    namespace Detail
    {
        template<class T> class RemoveLvalueReference
        {
        public:
            using Type = T;
        };

        template<class T> class RemoveLvalueReference<T&>
        {
        public:
            using Type = T;
        };
    }

    template<class Self> using RemoveLvalueReference = Detail::RemoveLvalueReference<Self>::Type;
}

#endif
#endif