#if lucy_major >= 0 and lucy_middle >= 0 and lucy_minor >= 1
#ifndef lucy_core_null_pointer
#define lucy_core_null_pointer

namespace Lucy
{
    using NullPointer = decltype(nullptr);
}

#endif
#endif