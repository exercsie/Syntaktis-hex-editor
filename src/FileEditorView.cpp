#include "FileEditorView.hpp"
#include "../Dependencies/imgui/imgui.h"
#include "../Dependencies/imgui/misc/cpp/imgui_stdlib.h"
#include "Gui.hpp"
#include "File.hpp"

void FileEditorView::FileMainView(ImVec2& displaySize) {
    if(f.ofd.openedFilePath.empty()) {
        return;
    }

    const float halfSize = displaySize.x / 2;
    const float height = displaySize.y - 30.0f; // just below menu bar

    ImGui::SetNextWindowPos(ImVec2(0.0f, 30.0f), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(displaySize.x, height), ImGuiCond_Always);
    ImGui::SetNextWindowBgAlpha(1.0f); // Completely cover prior view
    ImGui::Begin("Edit File", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);

    hexEditorView(ImVec2(0.0f, 0.0f), halfSize, height);
    charEditorView(ImVec2(0.0f, 0.0f), halfSize, height);

    ImGui::End();
}

void FileEditorView::hexEditorView(const ImVec2&, const float halfSize, const float height) {
    ImGui::SetCursorPos(ImVec2(0.0f, 0.0f));
    ImGui::BeginChild("Hex Editor", ImVec2(halfSize + 300.0f, height), ImGuiChildFlags_Borders);
    ImGui::Text("HEX EDIT!");
    if(ImGui::InputText("##", &InputData.hex)) {
        InputData.chars = c.convertHexToChar(InputData.hex);
    }
    ImGui::EndChild();
}

void FileEditorView::charEditorView(const ImVec2&, const float halfSize, const float height) {
    ImGui::SetCursorPos(ImVec2(halfSize + 300, 0.0f));
    ImGui::BeginChild("Char Editor", ImVec2(halfSize, height), ImGuiChildFlags_Borders);
    ImGui::Text("Char EDIT!");
    if(ImGui::InputText("##", &InputData.chars)) {
        InputData.hex = c.convertCharsToHex(InputData.chars);
    }

    ImGui::EndChild();
} 