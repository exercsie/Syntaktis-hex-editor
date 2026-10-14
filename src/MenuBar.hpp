#pragma once

#include <cstdlib>         // std::getenv
#include <string>          // std::string
#include <filesystem>      // std::filesystem::path
#include <optional>        // std::optional

class MenuBar {
public:
    MenuBar() = default;
    ~MenuBar() = default;

    void menuBarView(GLFWwindow*);
    
private:
    void menuBarDialog();
    void menuLogic(GLFWwindow*);
    void createTextFile();
    void openFile();
    void saveFile();
    void quit(GLFWwindow*);

    struct MenuBarData {
        bool isReqToCreateNewTextFile = false;
        bool isReqToOpenFile = false;
        bool isReqToSaveFile = false;
        bool isReqToCloseProgram = false;
    };

    struct CreateFileData {
        char createTextFileName[16];
        const std::filesystem::path syntaktisHexEditorDirectory = std::filesystem::path(std::getenv("HOME")) / "Syntaktis-Hex-Editor/Created-Text-Files";
    };

    MenuBarData mbd;
    CreateFileData cfd;
};