#pragma once

#include <filesystem>           // std::filesystem
#include <cstdlib>              // std::getenv
#include <string>               // std::string

class File {
public:
    void createTextFile();
    void openFile();
    void openFileSelector();
    void saveFile();
    
    struct OpenedFileData {
        std::string openedFilePath;
        std::string fileContents;
    };
    
    OpenedFileData ofd;
    struct CreateFileData {
        char createTextFileName[16] = {};
        const std::filesystem::path syntaktisHexEditorDirectory = std::filesystem::path(std::getenv("HOME")) / "Syntaktis-Hex-Editor/Created-Text-Files";
    };
    

    CreateFileData cfd;
};