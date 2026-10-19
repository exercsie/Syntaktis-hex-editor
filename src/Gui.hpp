#pragma once

#include "../Dependencies/imgui/imgui.h"
#include "File.hpp"

#include <cstdint>              // std::uint8_t, std::uint32_t
#include <GLFW/glfw3.h>     

class Gui {
public:
    // Constructor / Destructor
    explicit Gui();
    explicit Gui(File& file) : f(file) {}
    ~Gui() = default; 

    // Views
    void MenuBarView(GLFWwindow*, ImVec2&);
    void InitialScreenView(ImVec2& displaySize, GLFWwindow* win);

    // General UI
    void displayCreateTextFilePopup();
    void displayUnsavedChangesPopup();
    [[nodiscard]] bool buttonColour(const char* name, ImVec4 v, ImVec2 size = ImVec2(100, 0));
    [[nodiscard]] ImFont* staticFontLoader(std::uint8_t* fontData, const std::uint32_t fontLength, float size = 20.0f);
private:
    bool openCreateTextFilePopup = false;
    File& f;
};