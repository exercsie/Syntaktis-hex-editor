#pragma once

#include "../Assets/Fonts/NotoSans.hpp"
#include "MenuBar.hpp"

#include <cstdint>          // std::uint8_t, std::uint32_t

class Gui {
public:
    Gui() = default;
    ~Gui() = default;

    void initialScreen(ImVec2& displaySize, GLFWwindow* win);
    bool buttonColour(const char* name, ImVec4 v, ImVec2 size = ImVec2(100, 0));
    [[nodiscard]] ImFont* staticFontLoader(std::uint8_t* fontData, const std::uint32_t fontLength, float size = 20.0f);
    void menuBarView(GLFWwindow* win) { mb.menuBarView(win); }
private:
    MenuBar mb;
};