#if lucy_major >= 0 and lucy_middle >= 0 and lucy_minor >= 1
#ifndef lucy_core_unsafe
#define lucy_core_unsafe
#define lucy_template_unreliable(...) <::Lucy::Detail::Unsafe __VA_OPT__(,) __VA_ARGS__>
#define lucy_unreliable(...) (const ::Lucy::Detail::Unsafe __VA_OPT__(,) __VA_ARGS__)
#define lucy_subscript_unsafe(...) [::Lucy::Detail::Unsafe{} __VA_OPT__(,) __VA_ARGS__]
#define lucy_braced_unsafe(...) {::Lucy::Detail::Unsafe{} __VA_OPT__(,) __VA_ARGS__}
#define lucy_template_unsafe(...) <::Lucy::Detail::Unsafe{} __VA_OPT__(,) __VA_ARGS__>
#define lucy_unsafe(...) (::Lucy::Detail::Unsafe{} __VA_OPT__(,) __VA_ARGS__)

namespace Lucy::Detail
{
    class [[nodiscard]] Unsafe final
    {
    public:
        constexpr ~Unsafe() noexcept = default;

        consteval Unsafe() noexcept = default;

        constexpr Unsafe(const Unsafe&) noexcept = delete;

        constexpr Unsafe(Unsafe&&) noexcept = delete;

        constexpr auto operator=(const Unsafe&) noexcept -> Unsafe& = delete;

        constexpr auto operator=(Unsafe&&) noexcept -> Unsafe& = delete;
    };
}
#endif
#endif