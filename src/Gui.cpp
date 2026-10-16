#include "../Dependencies/imgui/imgui.h"
#include "../Dependencies/imgui/backends/imgui_impl_glfw.h"
#include "../Dependencies/imgui/backends/imgui_impl_opengl3.h"
#include "Gui.hpp"

#include <GLFW/glfw3.h>

void Gui::initialScreen(ImVec2& displaySize, GLFWwindow* win) {
    ImGui::SetNextWindowPos(ImVec2(0.0f, 30.0f), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(displaySize.x, displaySize.y), ImGuiCond_Always);
    ImGui::Begin("Starter Screen", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);

    ImGui::SetCursorPos(ImVec2(displaySize.x * 0.5f - 225.0f, displaySize.y * 0.5f - 100.0f));
    ImGui::Text("Welcome to Syntaktis Hex Editor. Create a new text\nfile or open an existing one to start editing!");

    ImGui::SetCursorPos(ImVec2(displaySize.x * 0.5f - 225.0f, displaySize.y * 0.5f - 25.0f));
    if(buttonColour("New Text File", ImVec4(0.0f, 0.502f, 0.502f, 1.0f), ImVec2(200, 50))) {
        mb.requestNewTextFile();
    }

    ImGui::SetCursorPos(ImVec2(displaySize.x * 0.5f + 25.0f, displaySize.y * 0.5f - 25.0f));
    if(buttonColour("Open Text File", ImVec4(0.0f, 0.502f, 0.502f, 1.0f), ImVec2(200, 50))) {

    }

    ImGui::End();
}   

bool Gui::buttonColour(const char* name, ImVec4 v, ImVec2 size) {
    ImGui::PushStyleColor(ImGuiCol_Button, v);
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(v.x + 0.1f, v.y + 0.1f, v.z + 0.1f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(v.x - 0.1f, v.y - 0.1f, v.z - 0.1f, 1.0f));
    const bool isButtonPressed = ImGui::Button(name, size);
    ImGui::PopStyleColor(3);
    return isButtonPressed;
}

ImFont* Gui::staticFontLoader(std::uint8_t* fontData, const std::uint32_t fontLength, float size) {
    ImGuiIO& io = ImGui::GetIO();
    
    ImFontConfig cfg;
    cfg.FontDataOwnedByAtlas = false;
    return io.Fonts->AddFontFromMemoryTTF(fontData, fontLength, size, &cfg);
}
