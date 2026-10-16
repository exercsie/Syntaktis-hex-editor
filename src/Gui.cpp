#include "../Dependencies/imgui/imgui.h"
#include "Gui.hpp"

#include <format>               // std::format
#include <GLFW/glfw3.h>         // gl apis

void Gui::MenuView(GLFWwindow* win) {
    if(ImGui::BeginMainMenuBar()) {
        if(ImGui::BeginMenu("File")) {
            if(ImGui::MenuItem("New Text File")) {
                openCreateTextFilePopup = true;
                f.createTextFile();
            }

            ImGui::Separator();

            if(ImGui::MenuItem("Open File")) {
                f.openFileSelector();
            }

            ImGui::Separator();

            if(ImGui::MenuItem("Save File")) {
                f.saveFile();
            }

            ImGui::Separator();

            if(ImGui::MenuItem("Quit")) {
                glfwSetWindowShouldClose(win, true);
            }

            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }

    displayCreateTextFilePopup();
}

void Gui::InitialScreenView(ImVec2& displaySize, GLFWwindow* win) {
    ImGui::SetNextWindowPos(ImVec2(0.0f, 30.0f), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(displaySize.x, displaySize.y), ImGuiCond_Always);
    ImGui::Begin("Starter Screen", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);

    ImGui::SetCursorPos(ImVec2(displaySize.x * 0.5f - 225.0f, displaySize.y * 0.5f - 100.0f));
    ImGui::Text("Welcome to Syntaktis Hex Editor. Create a new text\nfile or open an existing one to start editing!");

    ImGui::SetCursorPos(ImVec2(displaySize.x * 0.5f - 225.0f, displaySize.y * 0.5f - 25.0f));
    if(buttonColour("New Text File", ImVec4(0.0f, 0.502f, 0.502f, 1.0f), ImVec2(200, 50))) {
        openCreateTextFilePopup = true;
    }

    ImGui::SetCursorPos(ImVec2(displaySize.x * 0.5f + 25.0f, displaySize.y * 0.5f - 25.0f));
    if(buttonColour("Open Text File", ImVec4(0.0f, 0.502f, 0.502f, 1.0f), ImVec2(200, 50))) {
        f.openFileSelector();
    }

    ImGui::End();
}   

void Gui::FileEditorView(ImVec2& displaySize) {
    if(f.ofd.openedFilePath.empty()) {
        return;
    }

    const float halfSize = displaySize.x / 2;
    const float height = displaySize.y - 30.0f; // just below menu bar

    ImGui::SetNextWindowPos(ImVec2(0.0f, 30.0f), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(displaySize.x, height), ImGuiCond_Always);
    ImGui::SetNextWindowBgAlpha(1.0f); // Completely cover prior view
    ImGui::Begin("Edit File", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);

    ImGui::SetCursorPos(ImVec2(0.0f, 0.0f));
    ImGui::BeginChild("Hex Editor", ImVec2(halfSize + 300.0f, height), ImGuiChildFlags_Borders);
    ImGui::Text("HEX EDIT!");
    ImGui::EndChild();

    ImGui::SetCursorPos(ImVec2(halfSize + 300, 0.0f));
    ImGui::BeginChild("Char Editor", ImVec2(halfSize, height), ImGuiChildFlags_Borders);
    ImGui::Text("Char EDIT!");
    ImGui::EndChild();

    ImGui::End();
}

void Gui::displayCreateTextFilePopup() {
    if(openCreateTextFilePopup) {
        ImGui::OpenPopup("Enter textfile name");
        openCreateTextFilePopup = false;
    }

    if(ImGui::BeginPopupModal("Enter textfile name", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
        const bool enter = ImGui::InputText("##", f.cfd.createTextFileName, sizeof(f.cfd.createTextFileName), ImGuiInputTextFlags_EnterReturnsTrue);

        if(ImGui::Button("Ok") || enter) {
            f.createTextFile();
            f.cfd.createTextFileName[0] = '\0'; // reset stale val
            ImGui::CloseCurrentPopup();
        }

        ImGui::SameLine();
        if(ImGui::Button("Cancel")) {
            f.cfd.createTextFileName[0] = '\0';
            ImGui::CloseCurrentPopup();
        }


        ImGui::EndPopup();
    }
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
