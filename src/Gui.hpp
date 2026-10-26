#pragma once

#include "../Dependencies/imgui/imgui.h"
#include "File.hpp"
#include "DynamicInputData.hpp"

#include <cstdint>              // std::uint8_t, std::uint32_t
#include <GLFW/glfw3.h>         // gl apis
#include <optional>             // std::optional
#include <string>               // std::string

class Gui {
public:
    struct ImageDetails { 
        float width{};
        float height{};
    };

    struct LoadedImage {
        std::uint32_t id;
        Gui::ImageDetails details;
    };

    // Constructor / Destructor
    explicit Gui();
    explicit Gui(File& file, ToggleCheckboxes& checkboxes) : f(file), tc(checkboxes) {}
    ~Gui() = default; 

    // Views
    void MenuBarView(GLFWwindow*, ImVec2&);
    void InitialScreenView(ImVec2& displaySize, GLFWwindow* win);
    void LogView(ImVec2& displaySize);

    // ** General UI **
    // Popups
    void displayCreateTextFilePopup();
    void displayUnsavedChangesPopup(GLFWwindow* win);
    static void displayUnsavedChangesOnDirectProgramClosure(GLFWwindow* w);

    // Other UI
    [[nodiscard]] bool buttonColour(const char* name, ImVec4 v, ImVec2 size = ImVec2(100, 0)) noexcept;
    [[nodiscard]] ImFont* staticFontLoader(std::uint8_t* fontData, const std::uint32_t fontLength, float size = 20.0f);

    // Images
    [[nodiscard]] static std::optional<std::uint32_t> imageLoader(const std::uint8_t* bytes, int length, ImageDetails& details);
    void loadImage() noexcept;
    const std::optional<LoadedImage>& getImage();

    ImageDetails imageDetails;
    LoadedImage loadedImage;
    bool destroyInitialScreenView = false;
private:
    std::uint32_t textureID;
    bool openCreateTextFilePopup = false;
    bool quitAfterPopup = false;
    bool createAfterPopup = false;
    void createAndOpenTextFile();
    ToggleCheckboxes& tc;
    File& f;
};