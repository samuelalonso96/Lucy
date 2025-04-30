#if lucy_major >= 0 and lucy_middle >= 0 and lucy_minor >= 1
#ifndef lucy_io_file
#define lucy_io_file
#include <string>
#include <vector>

namespace Lucy::IO::File
{
    [[nodiscard]] auto Read(const std::string path) noexcept -> std::vector<unsigned char>;
}

#endif
#endif