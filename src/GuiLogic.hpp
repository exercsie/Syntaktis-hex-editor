#pragma once

#include <cstdlib>         // std::getenv
#include <string>          // std::string
#include <filesystem>      // std::filesystem::path
#include <optional>        // std::optional

class GuiLogic {
public:
    GuiLogic() = default;
    ~GuiLogic() = default;

    void menuBarView(GLFWwindow*);
    void fileEditorView(ImVec2& displaySize);
    void requestNewTextFile() { mbd.isReqToCreateNewTextFile = true; }
    void requestToOpenFile() { mbd.isReqToOpenFile = true; }
    
private:
    void menuBarDialog();
    void menuLogic(GLFWwindow*);
    void createTextFile();
    void openFile();
    void openFileSelector();
    void saveFile();
    void quit(GLFWwindow*);

    struct MenuBarData {
        bool isReqToCreateNewTextFile = false;
        bool isReqToOpenFile = false;
        bool isReqToSaveFile = false;
        bool isReqToCloseProgram = false;
    };

    struct CreateFileData {
        char createTextFileName[16] = {};
        const std::filesystem::path syntaktisHexEditorDirectory = std::filesystem::path(std::getenv("HOME")) / "Syntaktis-Hex-Editor/Created-Text-Files";
    };

    struct OpenedFileData {
        std::string openedFilePath;
        std::string fileContents;
    };

    MenuBarData mbd;
    CreateFileData cfd;
    OpenedFileData ofd;
};