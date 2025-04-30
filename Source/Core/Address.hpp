#if lucy_major >= 0 and lucy_middle >= 0 and lucy_minor >= 1
#ifndef lucy_core_address
#define lucy_core_address

namespace Lucy
{
    template<class T> [[nodiscard]] constexpr auto Address(T& object) noexcept -> T*
    {
        return __builtin_addressof(object);
    }
}

#endif
#endif