#if lucy_major >= 0 and lucy_middle >= 0 and lucy_minor >= 1
#ifndef lucy_engine_vertex
#define lucy_engine_vertex

namespace Lucy::Engine
{
    struct [[nodiscard]] Vertex
    {
        float x, y, u, v;
    };
}

#endif
#endif