#pragma once

#include "../Assets/Fonts/NotoSans.hpp"
#include "GuiLogic.hpp"

#include <cstdint>          // std::uint8_t, std::uint32_t

class Gui {
public:
    Gui() = default;
    ~Gui() = default;

    void initialScreenView(ImVec2& displaySize, GLFWwindow* win);
    void menuBarView(GLFWwindow* win) { gl.menuBarView(win); }
    void fileEditorView(ImVec2& displaySize) { gl.fileEditorView(displaySize); };
    bool buttonColour(const char* name, ImVec4 v, ImVec2 size = ImVec2(100, 0));
    [[nodiscard]] ImFont* staticFontLoader(std::uint8_t* fontData, const std::uint32_t fontLength, float size = 20.0f);
private:
    GuiLogic gl;
};