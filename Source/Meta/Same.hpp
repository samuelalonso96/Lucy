#if lucy_major >= 0 and lucy_middle >= 0 and lucy_minor >= 1
#ifndef lucy_meta_same
#define lucy_meta_same

namespace Lucy::Meta
{
    namespace Detail
    {
        template<class, class> class Same
        {
        public:
            static consteval bool Value() noexcept
            {
                return false;
            }
        };

        template<class T> class Same<T, T>
        {
        public:
            static consteval bool Value() noexcept
            {
                return true;
            }
        };
    }

    template<class T, class U> concept Same = Detail::Same<T, U>::Value();
}

#endif
#endif