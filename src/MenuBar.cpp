#include "../Dependencies/imgui/imgui.h"
#include "../Dependencies/imgui/backends/imgui_impl_glfw.h"
#include "../Dependencies/imgui/backends/imgui_impl_opengl3.h"
#include "MenuBar.hpp"

#include <filesystem>           // std::filesystem
#include <fstream>              // std::ofstream
#include <GLFW/glfw3.h>


#include <iostream>

void MenuBar::menuBarView(GLFWwindow* win) {
    menuBarDialog();
    menuLogic(win);
}

void MenuBar::menuBarDialog() {
    if(ImGui::BeginMainMenuBar()) {
        if(ImGui::BeginMenu("File")) {
            if(ImGui::MenuItem("New Text File")) {
                mbd.isReqToCreateNewTextFile = true;
            }

            ImGui::Separator();

            if(ImGui::MenuItem("Open File")) {
                mbd.isReqToOpenFile = true;
            }

            ImGui::Separator();

            if(ImGui::MenuItem("Save File")) {
                mbd.isReqToSaveFile = true;
            }

            ImGui::Separator();

            if(ImGui::MenuItem("Quit")) {
                mbd.isReqToCloseProgram = true;
            }

            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
}

void MenuBar::menuLogic(GLFWwindow* win) {
    if(mbd.isReqToCreateNewTextFile) {
        ImGui::OpenPopup("Enter textfile name");
        mbd.isReqToCreateNewTextFile = false;
    }

    if(ImGui::BeginPopupModal("Enter textfile name", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
        const bool enter = ImGui::InputText("##", cfd.createTextFileName, sizeof(cfd.createTextFileName), ImGuiInputTextFlags_EnterReturnsTrue);

        if(ImGui::Button("Ok") || enter) {
            createTextFile();
            cfd.createTextFileName[0] = '\0'; // reset stale val
            ImGui::CloseCurrentPopup();
        }

        ImGui::SameLine();
        if(ImGui::Button("Cancel")) {
            cfd.createTextFileName[0] = '\0';
            ImGui::CloseCurrentPopup();
        }


        ImGui::EndPopup();
    }

    if(mbd.isReqToOpenFile) {
        openFile();
    }

    if(mbd.isReqToSaveFile) {
        saveFile();
    }

    if(mbd.isReqToCloseProgram) {
        quit(win);
    }
}

void MenuBar::createTextFile() {
    std::filesystem::create_directories(cfd.syntaktisHexEditorDirectory);
    std::filesystem::path fileName(cfd.createTextFileName);
    fileName = fileName.filename();
    
    if(fileName.extension() != ".txt") {
        fileName += ".txt";
    }

    std::ofstream createdTextFile(cfd.syntaktisHexEditorDirectory / fileName);
    if(createdTextFile.is_open()) {
        std::cout << fileName << " Created at " << cfd.syntaktisHexEditorDirectory << std::endl;
        // Ask user to save changes to prev file if changes are made
        // close current file
        // then open file, openFile();
    }
}

void MenuBar::openFile() {
    ImGui::Text("*Opens file*");
}

void MenuBar::saveFile() {
    ImGui::Text("*Saves File*");
}

void MenuBar::quit(GLFWwindow* win) {
    if(mbd.isReqToCloseProgram) {
        glfwSetWindowShouldClose(win, mbd.isReqToCloseProgram);
    }
}