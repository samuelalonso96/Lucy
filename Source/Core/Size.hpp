#if lucy_major >= 0 and lucy_middle >= 0 and lucy_minor >= 1
#ifndef lucy_core_size
#define lucy_core_size

namespace Lucy
{
    using Size = decltype(sizeof(bool));
}

#endif
#endif