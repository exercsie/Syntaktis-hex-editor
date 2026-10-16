#include "../Dependencies/imgui/imgui.h"
#include "../Dependencies/imgui/backends/imgui_impl_glfw.h"
#include "../Dependencies/imgui/backends/imgui_impl_opengl3.h"
#include "../Dependencies/portable-file-dialogs/portable-file-dialogs.h"
#include "File.hpp"

#include <filesystem>           // std::filesystem
#include <fstream>              // std::ofstream
#include <iostream>             // std::cout, std::endl
#include <string>               // std::string
#include <vector>               // std::vector

void File::createTextFile() {
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

void File::openFileSelector() {
    std::vector<std::string> chooseFile = pfd::open_file("Open File", cfd.syntaktisHexEditorDirectory.string(), {"Text Files", "*.txt", "All Files", "*" }).result();

    if(!chooseFile.empty()) {
        ofd.openedFilePath = chooseFile[0];
        openFile();
    }
}

void File::openFile() {
    std::ifstream file(ofd.openedFilePath);
    if(!file.is_open()) {
        std::cout << "failed to oepn file\n";
        return;
    }

    if(!ofd.fileContents.empty()) {
        std::cout << "recevied vals\n";
    }
}

void File::saveFile() {
    ImGui::Text("*Saves File*");
}