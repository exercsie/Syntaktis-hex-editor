#include "../Dependencies/imgui/imgui.h"
#include "Gui.hpp"

#include <format>               // std::format
#include <GLFW/glfw3.h>         // gl apis

#include <iostream>

void Gui::MenuBarView(GLFWwindow* win, ImVec2& displaySize) {
    if(ImGui::BeginMainMenuBar()) {
        if(ImGui::BeginMenu("File")) {
            if(ImGui::MenuItem("New Text File")) {
                openCreateTextFilePopup = true;
            }

            ImGui::Separator();

            if(ImGui::MenuItem("Open File")) {
                f.openFileSelector();
            }

            ImGui::Separator();

            if(ImGui::MenuItem("Save")) {
                const auto r = f.saveFile();
                if(r) {
                    std::cout << *r << std::endl;
                } else {
                    std::cout << r.error() << std::endl;
                }
            }

            if(ImGui::MenuItem("Save As...")) {
                const auto r = f.saveFileAs();
                if(!r) {
                    std::cout << r.error() << std::endl;
                }
            }

            ImGui::Separator();

            if(ImGui::MenuItem("Quit")) {
                if(f.isThereUnsavedChanges()) {
                    f.unsavedChangesPopup = true;
                    quitAfterPopup = true;
                } else {
                    glfwSetWindowShouldClose(win, true);
                }
            }

            ImGui::EndMenu();
        }

        // display path ton top bar
        ImGui::SetCursorPosX((displaySize.x / 2) - 300.0f);
        ImGui::Text(std::format("{}", f.ofd.openedFilePath).c_str());

        ImGui::EndMainMenuBar();
    }

    displayCreateTextFilePopup();
    displayUnsavedChangesPopup(win);
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

void Gui::displayCreateTextFilePopup() {
    if(openCreateTextFilePopup) {
        ImGui::OpenPopup("Enter textfile name");
        openCreateTextFilePopup = false;
    }

    if(ImGui::BeginPopupModal("Enter textfile name", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
        const bool enter = ImGui::InputText("##", f.cfd.createTextFileName, sizeof(f.cfd.createTextFileName), ImGuiInputTextFlags_EnterReturnsTrue);

        if(ImGui::Button("Ok") || enter) {
            const auto r = f.createTextFile();
            if(r) {
                f.cfd.createTextFileName[0] = '\0'; // reset stale val
                std::cout << *r << std::endl;
            } else {
                std::cout << r.error() << std::endl;
            }

            const auto of = f.openFile();
            if(of) {
                std::cout << *of << std::endl;
            } else {
                std::cout << of.error() << std::endl;
            }
            
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

void Gui::displayUnsavedChangesPopup(GLFWwindow* win) {
    if(f.unsavedChangesPopup) {
        ImGui::OpenPopup("Unsaved Changes");
        f.unsavedChangesPopup = false;
    }

    if(ImGui::BeginPopupModal("Unsaved Changes", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::Text("The file has not been saved");

        if(buttonColour("Save", ImVec4(0.0f, 1.0f, 0.0f, 0.5f))) {
            const auto r = f.saveFile();
            if(r) {
                std::cout << *r << std::endl;

                // Quit and save changes
                if(quitAfterPopup) {
                    glfwSetWindowShouldClose(win, quitAfterPopup);
                }

                f.ofd.openedFilePath = f.tempFilePath;

                const auto opened = f.openFile();
                if(!opened) {
                    std::cout << opened.error() << std::endl;
                }
            } else {
                std::cout << r.error() << std::endl;
            }

            ImGui::CloseCurrentPopup();
        }

        ImGui::SameLine();

        if(buttonColour("Don't save", ImVec4(1.0f, 0.0f, 0.0f, 0.5f))) {
            f.ofd.openedFilePath = f.tempFilePath;

            if(quitAfterPopup) {
                glfwSetWindowShouldClose(win, quitAfterPopup);
            }

            const auto r = f.openFile();
            if(!r) {
                std::cout << r.error() << std::endl;
            }

            ImGui::CloseCurrentPopup();
        }

        ImGui::SameLine();

        if(buttonColour("Cancel", ImVec4(0.5f, 0.5f, 0.5f, 0.5f))) {
            quitAfterPopup = false;
            f.tempFilePath.clear();
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