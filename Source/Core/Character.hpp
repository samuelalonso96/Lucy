#if lucy_major >= 0 and lucy_middle >= 0 and lucy_minor >= 1
#ifndef lucy_core_character
#define lucy_core_character
#include "Result.hpp"
#include "Encoding.hpp"

namespace Lucy
{
    class [[nodiscard]] NotAClosingPairedBracketCharacter final
    {
    public:
        constexpr ~NotAClosingPairedBracketCharacter() noexcept = default;

        constexpr NotAClosingPairedBracketCharacter() noexcept = default;

        constexpr NotAClosingPairedBracketCharacter(const NotAClosingPairedBracketCharacter&)
        noexcept = delete;

        constexpr NotAClosingPairedBracketCharacter(NotAClosingPairedBracketCharacter&&) noexcept =
        delete;

        constexpr auto operator=(const NotAClosingPairedBracketCharacter&) noexcept ->
        NotAClosingPairedBracketCharacter& = delete;

        constexpr auto operator=(NotAClosingPairedBracketCharacter&&) noexcept ->
        NotAClosingPairedBracketCharacter& = delete;
    };

    class [[nodiscard]] NotAnOpeningPairedBracketCharacter final
    {
    public:
        constexpr ~NotAnOpeningPairedBracketCharacter() noexcept = default;

        constexpr NotAnOpeningPairedBracketCharacter() noexcept = default;

        constexpr NotAnOpeningPairedBracketCharacter(const NotAnOpeningPairedBracketCharacter&)
        noexcept = delete;

        constexpr NotAnOpeningPairedBracketCharacter(NotAnOpeningPairedBracketCharacter&&) noexcept
        = delete;

        constexpr auto operator=(const NotAnOpeningPairedBracketCharacter&) noexcept ->
        NotAnOpeningPairedBracketCharacter& = delete;

        constexpr auto operator=(NotAnOpeningPairedBracketCharacter&&) noexcept ->
        NotAnOpeningPairedBracketCharacter& = delete;
    };

    class [[nodiscard]] NotAMirroredCharacter final
    {
    public:
        constexpr ~NotAMirroredCharacter() noexcept = default;

        constexpr NotAMirroredCharacter() noexcept = default;

        constexpr NotAMirroredCharacter(const NotAMirroredCharacter&) noexcept = delete;

        constexpr NotAMirroredCharacter(NotAMirroredCharacter&&) noexcept = delete;

        constexpr auto operator=(const NotAMirroredCharacter&) noexcept -> NotAMirroredCharacter& =
        delete;

        constexpr auto operator=(NotAMirroredCharacter&&) noexcept -> NotAMirroredCharacter& =
        delete;
    };

    template<Encoding encoding = Encoding::UTF8> class [[nodiscard]] Character
    {
        char8_t m_value;
    public:
        constexpr ~Character() noexcept = default;

        constexpr Character lucy_unreliable() noexcept{}

        constexpr Character() noexcept : m_value(0u){}

        constexpr Character(const Character&) noexcept = default;

        constexpr Character(Character&&) noexcept = default;

        constexpr auto operator=(const Character&) noexcept -> Character& = default;

        constexpr auto operator=(Character&&) noexcept -> Character& = default;

        constexpr Character(const char8_t character) noexcept : m_value(character){}

        [[nodiscard]] constexpr auto PairedBracket() const noexcept -> bool
        {
            return m_value == 0x28 or m_value == 0x29 or m_value == 0x5b or m_value == 0x5d or
            m_value == 0x7b or m_value == 0x7d;
        }

        [[nodiscard]] constexpr auto OpenPairedBracket() const noexcept -> bool
        {
            return m_value == 0x28 or m_value == 0x5b or m_value == 0x7b;
        }

        [[nodiscard]] constexpr auto ClosePairedBracket() const noexcept -> bool
        {
            return m_value == 0x29 or m_value == 0x5d or m_value == 0x7d;
        }

        [[nodiscard]] constexpr auto OpeningPairedBracket lucy_unreliable() const noexcept ->
        Character
        {
            switch(m_value)
            {
                case 0x29:
                    return Character(0x28);
                case 0x5d:
                    return Character(0x5b);
                case 0x7d:
                    return Character(0x7b);
                default:
                    return Character();
            }
        }

        [[nodiscard]] constexpr auto OpeningPairedBracket() const noexcept -> Result<Character,
        NotAClosingPairedBracketCharacter>
        {
            switch(m_value)
            {
                case 0x29:
                    return Character(0x28);
                case 0x5d:
                    return Character(0x5b);
                case 0x7d:
                    return Character(0x7b);
                default:
                    return NotAClosingPairedBracketCharacter();
            }
        }

        [[nodiscard]] constexpr auto ClosingPairedBracket lucy_unreliable() const noexcept ->
        Character
        {
            switch(m_value)
            {
                case 0x28:
                    return Character(0x29);
                case 0x5b:
                    return Character(0x5d);
                case 0x7b:
                    return Character(0x7d);
                default:
                    return Character();
            }
        }

        [[nodiscard]] constexpr auto ClosingPairedBracket() const noexcept -> Result<Character,
        NotAnOpeningPairedBracketCharacter>
        {
            switch(m_value)
            {
                case 0x28:
                    return Character(0x29);
                case 0x5b:
                    return Character(0x5d);
                case 0x7b:
                    return Character(0x7d);
                default:
                    return NotAnOpeningPairedBracketCharacter();
            }
        }

        [[nodiscard]] constexpr auto Mirrored() const noexcept -> bool
        {
            return m_value == 0x28 or m_value == 0x29 or m_value == 0x3c or m_value == 0x3e or
            m_value == 0x5b or m_value == 0x5d or m_value == 0x7b or m_value == 0x7d or m_value ==
            0xab or m_value == 0xbb;
        }

        [[nodiscard]] constexpr auto Mirror lucy_unreliable() const noexcept -> Character
        {
            switch(m_value)
            {
                case 0x28:
                    return Character(0x29);
                case 0x29:
                    return Character(0x28);
                case 0x3c:
                    return Character(0x3e);
                case 0x3e:
                    return Character(0x3c);
                case 0x5b:
                    return Character(0x5d);
                case 0x5d:
                    return Character(0x5b);
                case 0x7b:
                    return Character(0x7d);
                case 0x7d:
                    return Character(0x7b);
                case 0xab:
                    return Character(0xbb);
                case 0xbb:
                    return Character(0xab);
                default:
                    return Character();
            }
        }

        [[nodiscard]] constexpr auto Mirror() const noexcept -> Result<Character, NotAMirroredCharacter>
        {
            switch(m_value)
            {
                case 0x28:
                    return Character(0x29);
                case 0x29:
                    return Character(0x28);
                case 0x3c:
                    return Character(0x3e);
                case 0x3e:
                    return Character(0x3c);
                case 0x5b:
                    return Character(0x5d);
                case 0x5d:
                    return Character(0x5b);
                case 0x7b:
                    return Character(0x7d);
                case 0x7d:
                    return Character(0x7b);
                case 0xab:
                    return Character(0xbb);
                case 0xbb:
                    return Character(0xab);
                default:
                    return NotAMirroredCharacter();
            }
        }

        [[nodiscard]] constexpr auto BasicLatin() const noexcept -> bool
        {
            return m_value <= 0x7f;
        }

        [[nodiscard]] constexpr auto Latin1Supplement() const noexcept -> bool
        {
            return m_value > 0x7f;
        }

        [[nodiscard]] constexpr auto CaseFoldable() const noexcept -> bool
        {
            return (m_value >= 0x41 and m_value <= 0x5a) or (m_value >= 0xc0 and m_value <= 0xd6)
            or (m_value >= 0xd8 and m_value <= 0xf6) or (m_value >= 0xf8 and m_value <= 0xfe);
        }

        [[nodiscard]] constexpr auto CaseFolding lucy_unreliable() const noexcept -> Character
        {
            switch(m_value)
            {
                case 0x41:
                    return Character(0x61);
                case 0x42:
                    return Character(0x62);
                case 0x43:
                    return Character(0x63);
                case 0x44:
                    return Character(0x64);
                case 0x45:
                    return Character(0x65);
                case 0x46:
                    return Character(0x66);
                case 0x47:
                    return Character(0x67);
                case 0x48:
                    return Character(0x68);
                case 0x49:
                    return Character(0x69);
                case 0x4a:
                    return Character(0x6a);
                case 0x4b:
                    return Character(0x6b);
                case 0x4c:
                    return Character(0x6c);
                case 0x4d:
                    return Character(0x6d);
                case 0x4e:
                    return Character(0x6e);
                case 0x4f:
                    return Character(0x6f);
                case 0x50:
                    return Character(0x70);
                case 0x51:
                    return Character(0x71);
                case 0x52:
                    return Character(0x72);
                case 0x53:
                    return Character(0x73);
                case 0x54:
                    return Character(0x74);
                case 0x55:
                    return Character(0x75);
                default:
                    return Character();
            }
        }
    };
}

#endif
#endif