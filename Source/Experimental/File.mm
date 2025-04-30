#include "File.hpp"
#include <stdio.h>
#include <Foundation/Foundation.h>

namespace Lucy::IO::File
{
    [[nodiscard]] auto Read(const std::string path) noexcept -> std::vector<unsigned char>
    {
        const char* cpath = [[[NSBundle mainBundle] pathForResource: [NSString stringWithUTF8String: path.c_str()] ofType: nil] UTF8String];
        FILE* handler(fopen(cpath, "rb"));
        fseek(handler, 0, SEEK_END);
        std::vector<unsigned char> data(ftell(handler), 0);
        fseek(handler, 0, SEEK_SET);
        fread(data.data(), 1u, data.size(), handler);
        fclose(handler);
        return data;
    }
}