#if lucy_major >= 0 and lucy_middle >= 0 and lucy_minor >= 1
#ifndef lucy_core_some
#define lucy_core_some

namespace Lucy
{
    class [[nodiscard]] Some
    {
    public:
        constexpr ~Some() noexcept = default;

        constexpr Some() noexcept = default;

        constexpr Some(const Some&) noexcept = delete;

        constexpr Some(Some&&) noexcept = delete;

        constexpr auto operator=(const Some&) noexcept -> Some& = delete;

        constexpr auto operator=(Some&&) noexcept -> Some& = delete;
    };
}

#endif
#endif