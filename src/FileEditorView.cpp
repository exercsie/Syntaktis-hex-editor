#include "FileEditorView.hpp"
#include "../Dependencies/imgui/imgui.h"
#include "../Dependencies/imgui/misc/cpp/imgui_stdlib.h"
#include "Gui.hpp"
#include "File.hpp"

void FileEditorView::FileMainView(ImVec2& displaySize) {
    if(f.ofd.openedFilePath.empty()) {
        return;
    }

    const float height = displaySize.y - 30.0f; // just below menu bar
    const float hexWidth = displaySize.x / 2 + 300.0f;
    const float charWidth = displaySize.x - hexWidth;

    ImGui::SetNextWindowPos(ImVec2(0.0f, 30.0f), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(displaySize.x, height), ImGuiCond_Always);
    ImGui::SetNextWindowBgAlpha(1.0f); // Completely cover prior view
    ImGui::Begin("Edit File", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);

    hexEditorView(ImVec2(0.0f, 0.0f), hexWidth, height);
    charEditorView(ImVec2(0.0f, 0.0f), hexWidth, charWidth, height);

    ImGui::End();
}

void FileEditorView::hexEditorView(const ImVec2&, const float hexWidth, const float height) {
    ImGui::SetCursorPos(ImVec2(0.0f, 0.0f));
    ImGui::BeginChild("Hex Editor", ImVec2(hexWidth, height), ImGuiChildFlags_Borders);
    ImGui::Text("HEX EDIT!");
    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0, 0, 0, 0));
    ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(0, 0, 0, 0));
    ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4(0, 0, 0, 0));
    ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.0f);
    if(ImGui::InputTextMultiline("##", &InputData.hex, ImVec2(-FLT_MIN, -FLT_MIN), ImGuiInputTextFlags_WordWrap)) {
        InputData.chars = c.convertHexToChar(InputData.hex);
    }

    ImGui::PopStyleVar();
    ImGui::PopStyleColor(3);
    ImGui::EndChild();
}

void FileEditorView::charEditorView(const ImVec2&, const float firstX, const float width, const float height) {
    ImGui::SetCursorPos(ImVec2(firstX, 0.0f));
    ImGui::BeginChild("Char Editor", ImVec2(width, height), ImGuiChildFlags_Borders);
    ImGui::Text("Char EDIT!");
    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0, 0, 0, 0));
    ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(0, 0, 0, 0));
    ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4(0, 0, 0, 0));
    ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.0f);
    if(ImGui::InputTextMultiline("##", &InputData.chars, ImVec2(-FLT_MIN, -FLT_MIN), ImGuiInputTextFlags_WordWrap)) {
        InputData.hex = c.convertCharsToHex(InputData.chars);
    }

    ImGui::PopStyleVar();
    ImGui::PopStyleColor(3);
    ImGui::EndChild();
} 