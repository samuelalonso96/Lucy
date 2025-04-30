#if lucy_major >= 0 and lucy_middle >= 0 and lucy_minor >= 1
#ifndef lucy_core_optional
#define lucy_core_optional
#include "None.hpp"
#include "Some.hpp"
#include "Abort.hpp"
#include "Unsafe.hpp"
#include "../Meta/Equality.hpp"
#include "../Meta/Inequality.hpp"
#include "../Meta/Assignable.hpp"
#include "../Meta/Destructible.hpp"
#include "../Meta/Constructible.hpp"
#include "../Meta/CopyAssignable.hpp"
#include "../Meta/MoveAssignable.hpp"
#include "../Meta/CopyConstructible.hpp"
#include "../Meta/MoveConstructible.hpp"
#include "../Meta/DefaultConstructible.hpp"
#include "../Meta/TriviallyDestructible.hpp"
#include "../Meta/TriviallyCopyAssignable.hpp"
#include "../Meta/TriviallyMoveAssignable.hpp"
#include "../Meta/TriviallyCopyConstructible.hpp"
#include "../Meta/TriviallyMoveConstructible.hpp"
#include "../Meta/TriviallyDefaultConstructible.hpp"

namespace Lucy
{
    namespace Detail
    {
        template<class T> class Wrapper
        {
        public:
            T object;

            constexpr ~Wrapper() noexcept requires Meta::TriviallyDestructible<T> = default;

            constexpr ~Wrapper() noexcept requires(not Meta::TriviallyDestructible<T> and Meta::
            Destructible<T>){}

            constexpr Wrapper() noexcept requires Meta::TriviallyDefaultConstructible<T> = default;

            constexpr Wrapper() noexcept requires(not Meta::TriviallyDefaultConstructible<T> and
            Meta::DefaultConstructible<T>){}

            constexpr Wrapper(const Wrapper&) noexcept requires Meta::TriviallyCopyConstructible<T>
            = default;

            constexpr Wrapper(const Wrapper& rhs) noexcept requires(not Meta::
            TriviallyCopyConstructible<T> and Meta::CopyConstructible<T>) : object(rhs){}

            constexpr Wrapper(Wrapper&&) noexcept requires Meta::TriviallyMoveConstructible<T> =
            default;

            constexpr Wrapper(Wrapper&& rhs) noexcept requires(not Meta::TriviallyMoveConstructible
            <T> and Meta::MoveConstructible<T>) : object(lucy_forward(rhs)){}

            constexpr auto operator=(const Wrapper&) noexcept -> Wrapper& requires Meta::
            TriviallyCopyAssignable<T> = default;

            constexpr auto operator=(const Wrapper& rhs) noexcept -> Wrapper& requires(not Meta::
            TriviallyCopyAssignable<T> and Meta::CopyAssignable<T>)
            {
                object = rhs;
                return *this;
            }

            constexpr auto operator=(Wrapper&&) noexcept -> Wrapper& requires Meta::
            TriviallyMoveAssignable<T> = default;

            constexpr auto operator=(Wrapper&& rhs) noexcept -> Wrapper& requires(not Meta::
            TriviallyMoveAssignable<T> and Meta::MoveAssignable<T>)
            {
                object = lucy_forward(rhs);
                return *this;
            }

            constexpr Wrapper(auto&&... arguments) noexcept : object(lucy_forward(arguments)...){}

            constexpr auto operator=(auto&& rhs) noexcept -> void
            {
                object = lucy_forward(rhs);
            }
        };

        template<class T> union [[nodiscard]] WrapperUnion
        {
            Wrapper<T> object;

            constexpr WrapperUnion() noexcept{}

            constexpr WrapperUnion(const Some, auto&&... arguments) noexcept : object(lucy_forward(
            arguments)...){}
        };
    }

    template<class T> class [[nodiscard]] Optional
    {
        bool m_active = false;

        Detail::WrapperUnion<T> m_wrapper;
    public:
        constexpr ~Optional() noexcept
        {
            if(m_active)
                m_wrapper.object.~Wrapper();
        }

        constexpr Optional() noexcept = default;

        constexpr Optional() noexcept requires Meta::DefaultConstructible<T> : m_active(true),
        m_wrapper(Some{}){}

        constexpr Optional(const Optional& rhs) noexcept requires Meta::CopyConstructible<T> :
        m_active(rhs.m_active)
        {
            if(rhs.m_active)
                new(&m_wrapper.object) Detail::Wrapper<T>(rhs.m_wrapper.object);
        }

        constexpr Optional(Optional&& rhs) noexcept requires Meta::MoveConstructible<T> : m_active(
        rhs.m_active)
        {
            if(rhs.m_active)
                new(&m_wrapper.object) Detail::Wrapper<T>(lucy_forward(rhs.m_wrapper.object));
        }

        constexpr auto operator=(const Optional& rhs) noexcept -> Optional& requires((Meta::
        CopyConstructible<T> or Meta::CopyAssignable<T>) and Meta::Destructible<T>)
        {
            if(m_active)
            {
                if(rhs.m_active)
                    m_wrapper.object = rhs.m_wrapper.object;
                else
                {
                    m_active = false;
                    m_wrapper.object.~Wrapper();
                }
            }
            else if(rhs.m_active)
            {
                m_active = true;
                new(&m_wrapper.object) Detail::Wrapper<T>(rhs.m_wrapper.object);
            }
            return *this;
        }

        constexpr auto operator=(Optional&& rhs) noexcept -> Optional& requires((Meta::
        MoveConstructible<T> or Meta::MoveAssignable<T>) and Meta::Destructible<T>)
        {
            if(m_active)
            {
                if(rhs.m_active)
                    m_wrapper.object = lucy_forward(rhs.m_wrapper.object);
                else
                {
                    m_active = false;
                    m_wrapper.object.~Wrapper();
                }
            }
            else if(rhs.m_active)
            {
                m_active = true;
                new(&m_wrapper.object) Detail::Wrapper<T>(lucy_forward(rhs.m_wrapper.object));
            }
            return *this;
        }

        constexpr Optional(const None) noexcept{}

        constexpr Optional(const T& object) noexcept requires Meta::CopyConstructible<T> : m_active
        (true), m_wrapper(Some{}, object){}

        constexpr Optional(T&& object) noexcept requires Meta::MoveConstructible<T> : m_active(true
        ), m_wrapper(Some{}, lucy_forward(object)){}

        template<class FirstArgument, class... Arguments> requires Meta::Constructible<T,
        FirstArgument&&, Arguments&&...> constexpr Optional(FirstArgument&& first, Arguments&&...
        arguments) noexcept : m_active(true), m_wrapper(Some{}, lucy_forward(first), lucy_forward(
        arguments)...){}

        constexpr auto operator=(const None) noexcept -> Optional& requires Meta::Destructible<T>
        {
            if(m_active)
            {
                m_active = false;
                m_wrapper.object.~Wrapper();
            }
            return *this;
        }

        constexpr auto operator=(const T& object) noexcept -> Optional& requires(Meta::
        CopyConstructible<T> or Meta::CopyAssignable<T>)
        {
            if(m_active)
                m_wrapper.object = object;
            else
            {
                m_active = true;
                new(&m_wrapper.object) Detail::Wrapper<T>(object);
            }
            return *this;
        }

        constexpr auto operator=(T&& object) noexcept -> Optional& requires(Meta::MoveConstructible
        <T> or Meta::MoveAssignable<T>)
        {
            if(m_active)
                m_wrapper.object = lucy_forward(object);
            else
            {
                m_active = true;
                new(&m_wrapper.object) Detail::Wrapper<T>(lucy_forward(object));
            }
            return *this;
        }

        template<class U> requires(Meta::Constructible<T, U&&> or Meta::Assignable<T, U&&>)
        constexpr auto operator=(U&& rhs) noexcept -> Optional&
        {
            if(m_active)
                m_wrapper.object = lucy_forward(rhs);
            else
            {
                m_active = true;
                new(&m_wrapper.object) Detail::Wrapper<T>(lucy_forward(rhs));
            }
            return *this;
        }

        template<class Rhs> requires Meta::Equality<T, Rhs&&> [[nodiscard]] constexpr auto operator
        ==(Rhs&& object) const noexcept -> bool
        {
            return m_active ? m_wrapper.object.object == lucy_forward(object) : false;
        }

        template<class Rhs> requires Meta::Inequality<T, Rhs&&> [[nodiscard]] constexpr auto
        operator not_eq(Rhs&& object) const noexcept -> bool
        {
            return m_active ? m_wrapper.object.object not_eq lucy_forward(object) : true;
        }

        [[nodiscard]] constexpr auto operator==(const None) const noexcept -> bool
        {
            return not m_active;
        }

        [[nodiscard]] constexpr auto operator not_eq(const None) const noexcept -> bool
        {
            return m_active;
        }

        [[nodiscard]] constexpr auto operator==(const Some) const noexcept -> bool
        {
            return m_active;
        }

        [[nodiscard]] constexpr auto operator not_eq(const Some) const noexcept -> bool
        {
            return not m_active;
        }

        [[nodiscard]] constexpr operator bool() const noexcept
        {
            return m_active;
        }

        [[nodiscard]] constexpr auto Object lucy_unreliable() noexcept -> T&
        {
            return m_wrapper.object.object;
        }

        [[nodiscard]] constexpr auto Object() noexcept -> T&
        {
            return m_active ? m_wrapper.object.object : Abort();
        }
    };
}

#endif
#endif