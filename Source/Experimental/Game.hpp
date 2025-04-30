#if lucy_major >= 0 and lucy_middle >= 0 and lucy_minor >= 1
#ifndef lucy_engine_game
#define lucy_engine_game

namespace lucy_game
{
    auto Start() noexcept -> void;

    auto Update() noexcept -> void;

    auto Finish() noexcept -> void;
}

#endif
#endif