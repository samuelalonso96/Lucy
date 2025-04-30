#if lucy_major >= 0 and lucy_middle >= 0 and lucy_minor >= 1
#ifndef lucy_core_encoding
#define lucy_core_encoding

namespace Lucy
{
    enum class [[nodiscard]] Encoding : unsigned char
    {
        UTF8,
        UTF16,
        UTF32
    };
}

#endif
#endif