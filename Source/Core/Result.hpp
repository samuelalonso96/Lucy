#if lucy_major >= 0 and lucy_middle >= 0 and lucy_minor >= 1
#ifndef lucy_core_result
#define lucy_core_result
#include "Ok.hpp"
#include "Error.hpp"
#include "Optional.hpp"

namespace Lucy
{
    namespace Detail
    {
        template<class T, class U> union [[nodiscard]] BiwrapperUnion
        {
            Wrapper<T> former;

            Wrapper<U> latter;

            constexpr BiwrapperUnion() noexcept{}

            constexpr BiwrapperUnion(const Ok, auto&&... arguments) noexcept : former(lucy_forward(
            arguments)...){}

            constexpr BiwrapperUnion(const Error, auto&&... arguments) noexcept : latter(
            lucy_forward(arguments)...){}
        };

        enum class BiwrapperState : unsigned char
        {
            SNone,
            SOk,
            SError
        };
    }

    template<class Ok, class Error> class [[nodiscard]] Result
    {
        using enum Detail::BiwrapperState;

        Detail::BiwrapperState m_state = SNone;

        Detail::BiwrapperUnion<Ok, Error> m_wrapper;
    public:
        constexpr ~Result() noexcept
        {
            switch(m_state)
            {
                case SNone:
                break;
                case SOk:
                    m_wrapper.former.~Wrapper();
                break;
                case SError:
                    m_wrapper.latter.~Wrapper();
                break;
            }
        }

        constexpr Result() noexcept = default;

        constexpr Result() noexcept requires Meta::DefaultConstructible<Ok> : m_state(SOk),
        m_wrapper(Ok{}){}

        constexpr Result() noexcept requires(not Meta::DefaultConstructible<Ok> and Meta::
        DefaultConstructible<Error>) : m_state(SError), m_wrapper(Error{}){}

        constexpr Result(const Result& rhs) noexcept requires(Meta::CopyConstructible<Ok> or Meta::
        CopyConstructible<Error>) : m_state(rhs.m_state)
        {
            switch(rhs.m_state)
            {
                case SNone:
                break;
                case SOk:
                    new(&m_wrapper.former) Detail::Wrapper<Ok>(rhs.m_wrapper.former);
                break;
                case SError:
                    new(&m_wrapper.latter) Detail::Wrapper<Error>(rhs.m_wrapper.latter);
                break;
            }
        }

        constexpr Result(Result&& rhs) noexcept requires(Meta::MoveConstructible<Ok> or Meta::
        MoveConstructible<Error>) : m_state(rhs.m_state)
        {
            switch(rhs.m_state)
            {
                case SNone:
                break;
                case SOk:
                    new(&m_wrapper.former) Detail::Wrapper<Ok>(lucy_forward(rhs.m_wrapper.former));
                break;
                case SError:
                    new(&m_wrapper.latter) Detail::Wrapper<Error>(lucy_forward(rhs.m_wrapper.latter
                    ));
                break;
            }
        }

        constexpr auto operator=(const Result& rhs) noexcept -> Result& requires(Meta::
        CopyConstructible<Ok> or Meta::CopyConstructible<Error> or Meta::CopyAssignable<Ok> or Meta
        ::CopyAssignable<Error>)
        {
            switch(m_state)
            {
                case SNone:
                    switch(rhs.m_state)
                    {
                        case SNone:
                        break;
                        case SOk:
                            m_state = SOk;
                            new(&m_wrapper.former) Detail::Wrapper<Ok>(rhs.m_wrapper.former);
                        break;
                        case SError:
                            m_state = SError;
                            new(&m_wrapper.latter) Detail::Wrapper<Error>(rhs.m_wrapper.latter);
                        break;
                    }
                break;
                case SOk:
                    switch(rhs.m_state)
                    {
                        case SNone:
                            m_state = SNone;
                            m_wrapper.former.~Wrapper();
                        break;
                        case SOk:
                            m_wrapper.former = rhs.m_wrapper.former;
                        break;
                        case SError:
                            m_state = SError;
                            m_wrapper.former.~Wrapper();
                            new(&m_wrapper.latter) Detail::Wrapper<Error>(rhs.m_wrapper.latter);
                        break;
                    }
                break;
                case SError:
                    switch(rhs.m_state)
                    {
                        case SNone:
                            m_state = SNone;
                            m_wrapper.latter.~Wrapper();
                        break;
                        case SOk:
                            m_state = SOk;
                            m_wrapper.latter.~Wrapper();
                            new(&m_wrapper.former) Detail::Wrapper<Ok>(rhs.m_wrapper.former);
                        break;
                        case SError:
                            m_wrapper.latter = rhs.m_wrapper.latter;
                        break;
                    }
                break;
            }
            return *this;
        }

        constexpr auto operator=(Result&& rhs) noexcept -> Result& requires(Meta::MoveConstructible
        <Ok> or Meta::MoveConstructible<Error> or Meta::MoveAssignable<Ok> or Meta::MoveAssignable<
        Error>)
        {
            switch(m_state)
            {
                case SNone:
                    switch(rhs.m_state)
                    {
                        case SNone:
                        break;
                        case SOk:
                            m_state = SOk;
                            new(&m_wrapper.former) Detail::Wrapper<Ok>(lucy_forward(rhs.m_wrapper.
                            former));
                        break;
                        case SError:
                            m_state = SError;
                            new(&m_wrapper.latter) Detail::Wrapper<Error>(lucy_forward(rhs.
                            m_wrapper.latter));
                        break;
                    }
                break;
                case SOk:
                    switch(rhs.m_state)
                    {
                        case SNone:
                            m_state = SNone;
                            m_wrapper.former.~Wrapper();
                        break;
                        case SOk:
                            m_wrapper.former = lucy_forward(rhs.m_wrapper.former);
                        break;
                        case SError:
                            m_state = SError;
                            m_wrapper.former.~Wrapper();
                            new(&m_wrapper.latter) Detail::Wrapper<Error>(lucy_forward(rhs.
                            m_wrapper.latter));
                        break;
                    }
                break;
                case SError:
                    switch(rhs.m_state)
                    {
                        case SNone:
                            m_state = SNone;
                            m_wrapper.latter.~Wrapper();
                        break;
                        case SOk:
                            m_state = SOk;
                            m_wrapper.latter.~Wrapper();
                            new(&m_wrapper.former) Detail::Wrapper<Ok>(lucy_forward(rhs.m_wrapper.
                            former));
                        break;
                        case SError:
                            m_wrapper.latter = lucy_forward(rhs.m_wrapper.latter);
                        break;
                    }
                break;
            }
            return *this;
        }

        constexpr Result(const None) noexcept{}

        constexpr Result(const Ok& object) noexcept : m_state(SOk), m_wrapper(::Lucy::Ok{}, object)
        {}

        constexpr Result(Ok&& object) noexcept : m_state(SOk), m_wrapper(::Lucy::Ok{}, lucy_forward
        (object)){}

        constexpr Result(const Error& object) noexcept requires(not Meta::Same<Meta::
        RemoveReferences<Ok>, Meta::RemoveReferences<Error>>) : m_state(SError), m_wrapper(::Lucy::
        Error{}, object){}

        constexpr Result(Error&& object) noexcept requires(not Meta::Same<Meta::RemoveReferences<Ok
        >, Meta::RemoveReferences<Error>>) : m_state(SError), m_wrapper(::Lucy::Error{},
        lucy_forward(object)){}

        template<class FirstArgument, class... Arguments> requires Meta::Constructible<Ok,
        FirstArgument&&, Arguments&&...> constexpr Result(FirstArgument&& first, Arguments&&...
        arguments) noexcept : m_state(SOk), m_wrapper(::Lucy::Ok{}, lucy_forward(first),
        lucy_forward(arguments)...){}

        template<class FirstArgument, class... Arguments> requires(not Meta::Constructible<Ok,
        FirstArgument&&, Arguments&&...> and Meta::Constructible<Error, FirstArgument&&, Arguments
        &&...>) constexpr Result(FirstArgument&& first, Arguments&&... arguments) noexcept :
        m_state(SError), m_wrapper(::Lucy::Error{}, lucy_forward(first), lucy_forward(arguments)...
        ){}

        template<class FirstArgument, class... Arguments> requires Meta::Constructible<Ok,
        FirstArgument&&, Arguments&&...> constexpr Result(const ::Lucy::Ok, FirstArgument&& first,
        Arguments&&... arguments) noexcept : m_state(SOk), m_wrapper(::Lucy::Ok{}, lucy_forward(
        first), lucy_forward(arguments)...){}

        template<class FirstArgument, class... Arguments> requires Meta::Constructible<Error,
        FirstArgument&&, Arguments&&...> constexpr Result(const ::Lucy::Error, FirstArgument&&
        first, Arguments&&... arguments) noexcept : m_state(SError), m_wrapper(::Lucy::Error{},
        lucy_forward(first), lucy_forward(arguments)...){}

        constexpr auto operator=(const None) noexcept -> Result&
        {
            switch(m_state)
            {
                case SNone:
                break;
                case SOk:
                    m_state = SNone;
                    m_wrapper.former.~Wrapper();
                break;
                case SError:
                    m_state = SNone;
                    m_wrapper.latter.~Wrapper();
                break;
            }
            return *this;
        }

        constexpr auto operator=(const Ok& object) noexcept -> Result& requires(Meta::
        CopyConstructible<Ok> or Meta::CopyAssignable<Ok>)
        {
            switch(m_state)
            {
                case SNone:
                    m_state = SOk;
                    new(&m_wrapper.former) Detail::Wrapper<Ok>(object);
                break;
                case SOk:
                    m_wrapper.former = object;
                break;
                case SError:
                    m_state = SOk;
                    m_wrapper.latter.~Wrapper();
                    new(&m_wrapper.former) Detail::Wrapper<Ok>(object);
                break;
            }
            return *this;
        }

        constexpr auto operator=(Ok&& object) noexcept -> Result& requires(Meta::MoveConstructible<
        Ok> or Meta::MoveAssignable<Ok>)
        {
            switch(m_state)
            {
                case SNone:
                    m_state = SOk;
                    new(&m_wrapper.former) Detail::Wrapper<Ok>(lucy_forward(object));
                break;
                case SOk:
                    m_wrapper.former = lucy_forward(object);
                break;
                case SError:
                    m_state = SOk;
                    m_wrapper.latter.~Wrapper();
                    new(&m_wrapper.former) Detail::Wrapper<Ok>(lucy_forward(object));
                break;
            }
            return *this;
        }

        constexpr auto operator=(const Error& object) noexcept -> Result& requires(Meta::
        CopyConstructible<Error> or Meta::CopyAssignable<Error>)
        {
            switch(m_state)
            {
                case SNone:
                    m_state = SError;
                    new(&m_wrapper.latter) Detail::Wrapper<Error>(object);
                break;
                case SOk:
                    m_state = SError;
                    m_wrapper.former.~Wrapper();
                    new(&m_wrapper.latter) Detail::Wrapper<Error>(object);
                break;
                case SError:
                    m_wrapper.latter = object;
                break;
            }
            return *this;
        }

        constexpr auto operator=(Error&& object) noexcept -> Result& requires(Meta::
        MoveConstructible<Error> or Meta::MoveAssignable<Error>)
        {
            switch(m_state)
            {
                case SNone:
                    m_state = SError;
                    new(&m_wrapper.latter) Detail::Wrapper<Error>(lucy_forward(object));
                break;
                case SOk:
                    m_state = SError;
                    m_wrapper.former.~Wrapper();
                    new(&m_wrapper.latter) Detail::Wrapper<Error>(lucy_forward(object));
                break;
                case SError:
                    m_wrapper.latter = lucy_forward(object);
                break;
            }
            return *this;
        }

        template<class T> requires(Meta::Constructible<Ok, T&&> or Meta::Assignable<Ok, T&&>)
        constexpr auto operator=(T&& rhs) noexcept -> Result&
        {
            switch(m_state)
            {
                case SNone:
                    m_state = SOk;
                    new(&m_wrapper.former) Detail::Wrapper<Ok>(lucy_forward(rhs));
                break;
                case SOk:
                    m_wrapper.former = lucy_forward(rhs);
                break;
                case SError:
                    m_state = SOk;
                    m_wrapper.latter.~Wrapper();
                    new(&m_wrapper.former) Detail::Wrapper<Ok>(lucy_forward(rhs));
                break;
            }
            return *this;
        }

        template<class T> requires(not(Meta::Constructible<Ok, T&&> or Meta::Assignable<Ok, T&&>)
        and (Meta::Constructible<Error, T&&> or Meta::Assignable<Error, T&&>)) constexpr auto
        operator=(T&& rhs) noexcept -> Result&
        {
            switch(m_state)
            {
                case SNone:
                    m_state = SError;
                    new(&m_wrapper.latter) Detail::Wrapper<Error>(lucy_forward(rhs));
                break;
                case SOk:
                    m_state = SError;
                    m_wrapper.former.~Wrapper();
                    new(&m_wrapper.latter) Detail::Wrapper<Error>(lucy_forward(rhs));
                break;
                case SError:
                    m_wrapper.latter = lucy_forward(rhs);
                break;
            }
            return *this;
        }

        template<class T> requires Meta::Equality<Ok, T&&> [[nodiscard]] constexpr auto operator==(
        T&& rhs) const noexcept -> bool
        {
            return m_state == SOk ? m_wrapper.former.object == lucy_forward(rhs) : false;
        }

        template<class T> requires Meta::Inequality<Ok, T&&> [[nodiscard]] constexpr auto operator
        not_eq(T&& rhs) const noexcept -> bool
        {
            return m_state == SOk ? m_wrapper.former.object not_eq lucy_forward(rhs) : true;
        }

        template<class T> requires(not Meta::Equality<Ok, T&&> and Meta::Equality<Error, T&&>)
        [[nodiscard]] constexpr auto operator==(T&& rhs) const noexcept -> bool
        {
            return m_state == SError ? m_wrapper.latter.object == lucy_forward(rhs) : false;
        }

        template<class T> requires(not Meta::Inequality<Ok, T&&> and Meta::Inequality<Error, T&&>)
        [[nodiscard]] constexpr auto operator not_eq(T&& rhs) const noexcept -> bool
        {
            return m_state == SError ? m_wrapper.latter.object not_eq lucy_forward(rhs) : true;
        }

        [[nodiscard]] constexpr auto operator==(const None) const noexcept -> bool
        {
            return m_state == SNone;
        }

        [[nodiscard]] constexpr auto operator not_eq(const None) const noexcept -> bool
        {
            return m_state not_eq SNone;
        }

        [[nodiscard]] constexpr auto operator==(const ::Lucy::Ok) const noexcept -> bool
        {
            return m_state == SOk;
        }

        [[nodiscard]] constexpr auto operator not_eq(const ::Lucy::Ok) const noexcept -> bool
        {
            return m_state not_eq SOk;
        }

        [[nodiscard]] constexpr auto operator==(const ::Lucy::Error) const noexcept -> bool
        {
            return m_state == SError;
        }

        [[nodiscard]] constexpr auto operator not_eq(const ::Lucy::Error) const noexcept -> bool
        {
            return m_state not_eq SError;
        }

        [[nodiscard]] constexpr operator bool() const noexcept
        {
            return m_state == SOk;
        }

        [[nodiscard]] constexpr auto Fine lucy_unreliable() noexcept -> Ok&
        {
            return m_wrapper.former.object;
        }

        [[nodiscard]] constexpr auto Fine() noexcept -> Optional<Ok&>
        {
            if(m_state == SOk)
                return m_wrapper.former.object;
            return Optional<Ok&>();
        }

        [[nodiscard]] constexpr auto Fault lucy_unreliable() noexcept -> Error&
        {
            return m_wrapper.latter.object;
        }

        [[nodiscard]] constexpr auto Fault() noexcept -> Optional<Error&>
        {
            if(m_state == SError)
                return m_wrapper.latter.object;
            return Optional<Error&>();
        }
    };
}

#endif
#endif