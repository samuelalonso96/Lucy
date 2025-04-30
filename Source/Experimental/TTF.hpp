#if lucy_major >= 0 and lucy_middle >= 0 and lucy_minor >= 1
#ifndef lucy_formats_ttf
#define lucy_formats_ttf
#include <vector>

namespace Lucy::Formats
{
    class [[nodiscard]] TTF
    {
    public:
        TTF(const std::vector<unsigned char>& content) noexcept;
    };
}

#endif
#endif