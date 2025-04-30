#if lucy_major >= 0 and lucy_middle >= 0 and lucy_minor >= 1
#ifndef lucy_core_move
#define lucy_core_move
#include "../Meta/RemoveLvalueReference.hpp"
#define lucy_move(moved) static_cast<::Lucy::Meta::RemoveLvalueReference<decltype(moved)>&&>(moved)
#endif
#endif