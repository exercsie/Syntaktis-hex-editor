#include "../Dependencies/imgui/imgui.h"
#include "../Dependencies/imgui/backends/imgui_impl_glfw.h"
#include "../Dependencies/imgui/backends/imgui_impl_opengl3.h"
#include "../Dependencies/portable-file-dialogs/portable-file-dialogs.h"
#include "File.hpp"
#include "ByteLogic.hpp"
#include "ErrorHandling.hpp"

#include <filesystem>           // std::filesystem
#include <format>               // std::format
#include <fstream>              // std::ofstream
#include <iterator>             // std::istreambuf_iterator
#include <string>               // std::string
#include <vector>               // std::vector

std::expected<std::string, std::string> File::createTextFile() noexcept {
    std::filesystem::create_directories(cfd.syntaktisHexEditorDirectory);
    std::filesystem::path fileName(cfd.createTextFileName);
    fileName = fileName.filename();
    
    if(fileName.extension() != ".txt") {
        fileName += ".txt";
    }

    const std::filesystem::path fullPath = cfd.syntaktisHexEditorDirectory / fileName;

    std::ofstream createdTextFile(fullPath);
    if(!createdTextFile.is_open()) {
        return std::unexpected(std::format("Failed to open {}!", fileName.string()));
    }
    
    // clear previous values after creating new textfile
    InputData.chars.clear();
    InputData.hex.clear();
    ofd.fileContents.clear();
    ofd.openedFilePath = fullPath.string();
    return std::format("Created {}", fileName.string());
}

std::expected<std::string, std::string> File::openFile() noexcept {
    std::ifstream file(ofd.openedFilePath, std::ios::binary);
    if(!file.is_open()) {
        return std::unexpected(std::format("Failed to open {}!", ofd.openedFilePath));
    }
    
    // read data until the end of the file and assign to std::string fileContents
    ofd.fileContents.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()); //https://www.tutorialspoint.com/cpp_standard_library/cpp_iterator_istreambuf_iterator.htm

    if(file.bad()) {
        return std::unexpected(std::format("Failed to read {}!", ofd.openedFilePath));
    }

    ofd.originalContents = ofd.fileContents;

    InputData.chars = ofd.fileContents;
    InputData.hex = Conversion::convertCharsToHex(InputData.chars);
    return std::format("Opened {}", ofd.openedFilePath);
}

void File::openFileSelector() noexcept {
    std::vector<std::string> chooseFile = pfd::open_file("Open File", cfd.syntaktisHexEditorDirectory.string(), {"Text Files", "*.txt", "All Files", "*" }).result();

    if(!chooseFile.empty()) {
        if(isThereUnsavedChanges()) {
            tempFilePath = chooseFile[0];
            unsavedChangesPopup = true;
            return;
        }

        ofd.openedFilePath = chooseFile[0];
        const auto r = openFile();
        ErrorHandling::templateErrorHandling(r);
    }
}

std::expected<std::string, std::string> File::saveFile() noexcept {
    if(ofd.openedFilePath.empty()) {
        return std::unexpected("There is no file to save!");
    }

    std::ofstream file(ofd.openedFilePath, std::ios::binary | std::ios::trunc);
    if(!file.is_open()) {
        return std::unexpected(std::format("Failed to save {}!", ofd.openedFilePath));
    }

    file.write(ofd.fileContents.data(), static_cast<std::streamsize>(ofd.fileContents.size()));
    if(!file) {
        return std::unexpected(std::format("Faile to write to {}!", ofd.openedFilePath));
    }

    // Update original contents to remove invokation of unsaved changes
    ofd.originalContents = ofd.fileContents;

    return std::format("File saved successfully at {}", ofd.openedFilePath);
}

std::expected<void, std::string> File::saveFileAs() noexcept {
    if(ofd.openedFilePath.empty()) {
        return std::unexpected("There is no file to save!");
    }

    const std::string path = pfd::save_file("Save File As", cfd.syntaktisHexEditorDirectory.string(), { "Text Files", "*.txt", "All Files", "*" }).result();

    // if user clicks cancel just return
    if(path.empty()) {
        return {};
    }

    ofd.openedFilePath = path;

    const auto r = saveFile();
    ErrorHandling::templateErrorHandling(r);
    return {};
}