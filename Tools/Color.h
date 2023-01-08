#pragma once
#include <cstdint>

namespace Color
{
    struct Color
    {
        uint8_t r;
        uint8_t g;
        uint8_t b;
    };

    static const Color White{255, 255, 255};
    static const Color Black{0, 0, 0};
    static const Color Red{255, 0, 0};
    static const Color Green{0, 255, 0};
    static const Color Blue{0, 0, 255};
    static const Color Yellow{255, 255, 0};
    static const Color LightYellow{255, 255, 224};
    static const Color LightBlue{173, 217, 230};
    static const Color LightPink{255, 181, 194};
    static const Color LightGreen{143, 237, 143};
};