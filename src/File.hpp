#pragma once

#include "FileEditorView.hpp"

#include <cstdlib>              // std::getenv
#include <expected>             // std::expected, std::unexpected
#include <filesystem>           // std::filesystem
#include <string>               // std::string

class File {
public:
    // Constructor / Destructor
    explicit File(DynamicInputData& DynamicInputData) : InputData(DynamicInputData) {}
    ~File() = default;

    // Menu options
    std::expected<std::string, std::string> createTextFile();
    std::expected<std::string, std::string> openFile();
    void openFileSelector();
    std::expected<std::string, std::string> saveFile();
    
    // Data
    struct OpenedFileData {
        std::string openedFilePath;
        std::string fileContents;
    };
    
    struct CreateFileData {
        char createTextFileName[16]{};
        const std::filesystem::path syntaktisHexEditorDirectory = std::filesystem::path(std::getenv("HOME")) / "Syntaktis-Hex-Editor/Created-Text-Files";
    };
    
    OpenedFileData ofd;
    CreateFileData cfd;
private:
    DynamicInputData& InputData;
};