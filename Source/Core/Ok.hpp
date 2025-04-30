#if lucy_major >= 0 and lucy_middle >= 0 and lucy_minor >= 1
#ifndef lucy_core_ok
#define lucy_core_ok

namespace Lucy
{
    class [[nodiscard]] Ok
    {
    public:
        constexpr ~Ok() noexcept = default;

        constexpr Ok() noexcept = default;

        constexpr Ok(const Ok&) noexcept = delete;

        constexpr Ok(Ok&&) noexcept = delete;

        constexpr auto operator=(const Ok&) noexcept -> Ok& = delete;

        constexpr auto operator=(Ok&&) noexcept -> Ok& = delete;
    };
}

#endif
#endif