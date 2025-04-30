#if lucy_major >= 0 and lucy_middle >= 0 and lucy_minor >= 1
#ifndef lucy_core_error
#define lucy_core_error

namespace Lucy
{
    class [[nodiscard]] Error
    {
    public:
        constexpr ~Error() noexcept = default;

        constexpr Error() noexcept = default;

        constexpr Error(const Error&) noexcept = delete;

        constexpr Error(Error&&) noexcept = delete;

        constexpr auto operator=(const Error&) noexcept -> Error& = delete;

        constexpr auto operator=(Error&&) noexcept -> Error& = delete;
    };
}

#endif
#endif