#pragma once

#include "../Assets/Fonts/NotoSans.hpp"

#include <cstdint>          // std::uint8_t, std::uint32_t

class Gui {
public:
    Gui() = default;
    ~Gui() = default;

    [[nodiscard]] ImFont* staticFontLoader(std::uint8_t* fontData, const std::uint32_t fontLength, float size = 20.0f);
private:

};