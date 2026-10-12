#include "../Dependencies/imgui/imgui.h"
#include "../Dependencies/imgui/backends/imgui_impl_glfw.h"
#include "../Dependencies/imgui/backends/imgui_impl_opengl3.h"
#include "MenuBar.hpp"

#include <GLFW/glfw3.h>

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
        createTextFile();
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
    ImGui::Text("*Creates text file*");
    mbd.isReqToCreateNewTextFile = false;
}

void MenuBar::openFile() {
    ImGui::Text("*Opens file*");
    mbd.isReqToOpenFile = false;
}

void MenuBar::saveFile() {
    ImGui::Text("*Saves File*");
    mbd.isReqToSaveFile = false;
}

void MenuBar::quit(GLFWwindow* win) {
    if(mbd.isReqToCloseProgram) {
        glfwSetWindowShouldClose(win, mbd.isReqToCloseProgram);
    }
}