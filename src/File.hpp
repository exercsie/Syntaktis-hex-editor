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
    std::expected<std::string, std::string> createTextFile() noexcept;
    std::expected<std::string, std::string> openFile() noexcept;
    void openFileSelector() noexcept;
    std::expected<std::string, std::string> saveFile() noexcept;
    std::expected<void, std::string> saveFileAs() noexcept;

    // Checkers
    [[nodiscard]] bool isThereUnsavedChanges() const noexcept { return ofd.fileContents != ofd.originalContents; }

    // Data
    struct OpenedFileData {
        std::string openedFilePath;
        std::string fileContents;
        std::string originalContents;
    };
    
    struct CreateFileData {
        char createTextFileName[16]{};
        const std::filesystem::path syntaktisHexEditorDirectory = std::filesystem::path(std::getenv("HOME")) / "Syntaktis-Hex-Editor/Created-Text-Files";
    };
    
    OpenedFileData ofd;
    CreateFileData cfd;
    std::string tempFilePath;
    bool unsavedChangesPopup = false;
private:
    DynamicInputData& InputData;
};