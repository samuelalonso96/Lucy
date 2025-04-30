#if lucy_major >= 0 and lucy_middle >= 0 and lucy_minor >= 1
#ifndef lucy_core_none
#define lucy_core_none

namespace Lucy
{
    class [[nodiscard]] None
    {
    public:
        constexpr ~None() noexcept = default;

        constexpr None() noexcept = default;

        constexpr None(const None&) noexcept = delete;

        constexpr None(None&&) noexcept = delete;

        constexpr auto operator=(const None&) noexcept -> None& = delete;

        constexpr auto operator=(None&&) noexcept -> None& = delete;
    };
}

#endif
#endif