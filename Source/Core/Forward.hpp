#if lucy_major >= 0 and lucy_middle >= 0 and lucy_minor >= 1
#ifndef lucy_core_forward
#define lucy_core_forward
#define lucy_forward(forwarded) static_cast<decltype(forwarded)&&>(forwarded)
#endif
#endif