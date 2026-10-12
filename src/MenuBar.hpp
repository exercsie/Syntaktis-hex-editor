#pragma once

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

    MenuBarData mbd;
};