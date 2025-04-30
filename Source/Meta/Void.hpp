#if lucy_major >= 0 and lucy_middle >= 0 and lucy_minor >= 1
#ifndef lucy_meta_void
#define lucy_meta_void

namespace Lucy::Meta
{
    namespace Detail
    {
        template<class> class Void
        {
        public:
            static consteval bool Value() noexcept
            {
                return false;
            }
        };

        template<> class Void<void>
        {
        public:
            static consteval bool Value() noexcept
            {
                return true;
            }
        };

        template<> class Void<volatile void>
        {
        public:
            static consteval bool Value() noexcept
            {
                return true;
            }
        };

        template<> class Void<const void>
        {
        public:
            static consteval bool Value() noexcept
            {
                return true;
            }
        };

        template<> class Void<volatile const void>
        {
        public:
            static consteval bool Value() noexcept
            {
                return true;
            }
        };
    }

    template<class T> concept Void = Detail::Void<T>::Value();
}

#endif
#endif