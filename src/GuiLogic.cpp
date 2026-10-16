#include "../Dependencies/imgui/imgui.h"
#include "../Dependencies/imgui/backends/imgui_impl_glfw.h"
#include "../Dependencies/imgui/backends/imgui_impl_opengl3.h"
#include "../Dependencies/portable-file-dialogs/portable-file-dialogs.h"
#include "GuiLogic.hpp"

#include <filesystem>           // std::filesystem
#include <format>               // std::format
#include <fstream>              // std::ofstream
#include <GLFW/glfw3.h>         // gl apis
#include <vector>               // std::vector

#include <iostream>

void GuiLogic::menuBarView(GLFWwindow* win) {
    menuBarDialog();
    menuLogic(win);
}

void GuiLogic::menuBarDialog() {
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

void GuiLogic::menuLogic(GLFWwindow* win) {
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
        mbd.isReqToOpenFile = false;
        openFileSelector();
    }

    if(mbd.isReqToSaveFile) {
        saveFile();
    }

    if(mbd.isReqToCloseProgram) {
        quit(win);
    }
}

void GuiLogic::createTextFile() {
    std::filesystem::create_directories(cfd.syntaktisHexEditorDirectory);
    std::filesystem::path fileName(cfd.createTextFileName);
    fileName = fileName.filename();
    
    if(fileName.extension() != ".txt") {
        fileName += ".txt";
    }

    const std::filesystem::path fullPath = cfd.syntaktisHexEditorDirectory / fileName;

    std::ofstream createdTextFile(fullPath);
    if(!createdTextFile.is_open()) {
        std::cout << "file failed to open\n";
        return;
    }
    
    std::cout << fileName << " Created at " << cfd.syntaktisHexEditorDirectory << std::endl;
    ofd.openedFilePath = fullPath.string();
    openFile();
}

void GuiLogic::openFileSelector() {
    std::vector<std::string> chooseFile = pfd::open_file("Open File", cfd.syntaktisHexEditorDirectory.string(), {"Text Files", "*.txt", "All Files", "*" }).result();

    if(!chooseFile.empty()) {
        ofd.openedFilePath = chooseFile[0];
        openFile();
    }
}

void GuiLogic::openFile() {
    std::ifstream file(ofd.openedFilePath);
    if(!file.is_open()) {
        std::cout << "failed to oepn file\n";
        return;
    }

    if(!ofd.fileContents.empty()) {
        std::cout << "recevied vals\n";
    }
}


void GuiLogic::saveFile() {
    ImGui::Text("*Saves File*");
}

void GuiLogic::quit(GLFWwindow* win) {
    if(mbd.isReqToCloseProgram) {
        glfwSetWindowShouldClose(win, mbd.isReqToCloseProgram);
    }
}

void GuiLogic::fileEditorView(ImVec2& displaySize) {
    if(ofd.openedFilePath.empty()) {
        return;
    }

    ImGui::SetNextWindowPos(ImVec2(0.0f, 30.0f), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(displaySize.x, displaySize.y - 30.0f), ImGuiCond_Always);
    ImGui::Begin("Edit file", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
    
    ImGui::Text(std::format("{}", ofd.openedFilePath).c_str());

    ImGui::End();
}