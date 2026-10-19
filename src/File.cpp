#include "../Dependencies/imgui/imgui.h"
#include "../Dependencies/imgui/backends/imgui_impl_glfw.h"
#include "../Dependencies/imgui/backends/imgui_impl_opengl3.h"
#include "../Dependencies/portable-file-dialogs/portable-file-dialogs.h"
#include "File.hpp"

#include <filesystem>           // std::filesystem
#include <format>               // std::format
#include <fstream>              // std::ofstream
#include <iostream>             // std::cout, std::endl
#include <string>               // std::string
#include <vector>               // std::vector

std::expected<std::string, std::string> File::createTextFile() {
    std::filesystem::create_directories(cfd.syntaktisHexEditorDirectory);
    std::filesystem::path fileName(cfd.createTextFileName);
    fileName = fileName.filename();
    
    if(fileName.extension() != ".txt") {
        fileName += ".txt";
    }

    const std::filesystem::path fullPath = cfd.syntaktisHexEditorDirectory / fileName;

    std::ofstream createdTextFile(fullPath);
    if(!createdTextFile.is_open()) {
        return std::unexpected(std::format("Failed to open {}", fileName.string()));
    }
    
    ofd.openedFilePath = fullPath.string();
    return std::format("Created {}", fileName.string());
}

std::expected<std::string, std::string> File::openFile() {
    std::ifstream file(ofd.openedFilePath, std::ios::binary);
    if(!file.is_open()) {
        return std::unexpected(std::format("Failed to open {}", ofd.openedFilePath));
    }
    
    if(!ofd.fileContents.empty()) {
        std::cout << "recevied vals\n";
    }

    return std::format("Opening path {}", ofd.openedFilePath);
}

void File::openFileSelector() {
    std::vector<std::string> chooseFile = pfd::open_file("Open File", cfd.syntaktisHexEditorDirectory.string(), {"Text Files", "*.txt", "All Files", "*" }).result();

    if(!chooseFile.empty()) {
        ofd.openedFilePath = chooseFile[0];
        const auto r = openFile();
        if(r) {
            std::cout << *r << std::endl;
        } else {
            std::cout << r.error() << std::endl;
        }
    }
}

std::expected<std::string, std::string> File::saveFile() {
    if(ofd.openedFilePath.empty()) {
        return std::unexpected("There is no file to save!");
    }

    std::ofstream file(ofd.openedFilePath, std::ios::binary | std::ios::trunc);
    if(!file.is_open()) {
        return std::unexpected(std::format("Failed to save {}", ofd.openedFilePath));
    }

    file.write(ofd.fileContents.data(), static_cast<std::streamsize>(ofd.fileContents.size()));
    if(!file) {
        return std::unexpected(std::format("Faile to write to {}", ofd.openedFilePath));
    }

    return std::format("File saved successfully at {}", ofd.openedFilePath);
}