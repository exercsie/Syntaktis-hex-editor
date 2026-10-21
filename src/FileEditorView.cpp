#include "../Dependencies/imgui/imgui.h"
#include "../Dependencies/imgui/misc/cpp/imgui_stdlib.h"
#include "FileEditorView.hpp"
#include "File.hpp"

#include <format>           // std::format

void FileEditorView::FileMainView(ImVec2& displaySize) {
    if(f.ofd.openedFilePath.empty()) {
        return;
    }

    // Heights
    const float menuBarHeight = 30.0f;
    const float footerHeight = 40.0f;
    const float windowWidth = displaySize.x;
    const float windowHeight = displaySize.y - menuBarHeight;
    const float editorHeight = windowHeight - footerHeight;

    // widths
    const float hexEditorWidth = windowWidth / 2.0f + 150.0f;
    const float charEditorWidth = windowWidth - hexEditorWidth;

    ImGui::SetNextWindowPos(ImVec2(0.0f, 30.0f), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(windowWidth, windowHeight), ImGuiCond_Always);
    ImGui::SetNextWindowBgAlpha(1.0f); // Completely cover prior view
    ImGui::Begin("Edit File", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBringToFrontOnFocus);

    hexEditorView(ImVec2(0.0f, 0.0f), hexEditorWidth, editorHeight);
    charEditorView(ImVec2(hexEditorWidth, 0.0f), hexEditorWidth, charEditorWidth, editorHeight);
    FooterView(ImVec2(0.0f, editorHeight), footerHeight, hexEditorWidth, charEditorWidth);

    ImGui::End();
}

void FileEditorView::hexEditorView(const ImVec2& pos, const float hexEditorWidth, const float editorHeight) {
    ImGui::SetCursorPos(pos);
    ImGui::BeginChild("Hex Editor", ImVec2(hexEditorWidth, editorHeight), ImGuiChildFlags_Borders);
    ImGui::Text("Hex:");
    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0, 0, 0, 0));
    ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(0, 0, 0, 0));
    ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4(0, 0, 0, 0));
    ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.0f);
    if(ImGui::InputTextMultiline("##", &InputData.hex, ImVec2(-FLT_MIN, -FLT_MIN), ImGuiInputTextFlags_WordWrap)) {
        InputData.chars = c.convertHexToChar(InputData.hex);
        f.ofd.fileContents = InputData.chars;
    }

    ImGui::PopStyleVar();
    ImGui::PopStyleColor(3);
    ImGui::EndChild();
}

void FileEditorView::charEditorView(const ImVec2& pos, const float hexEditorWidth, const float charEditorWidth, const float editorHeight) {
    ImGui::SetCursorPos(pos);
    ImGui::BeginChild("Char Editor", ImVec2(charEditorWidth, editorHeight), ImGuiChildFlags_Borders);
    ImGui::Text("Char:");
    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0, 0, 0, 0));
    ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(0, 0, 0, 0));
    ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4(0, 0, 0, 0));
    ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.0f);
    if(ImGui::InputTextMultiline("##", &InputData.chars, ImVec2(-FLT_MIN, -FLT_MIN), ImGuiInputTextFlags_WordWrap)) {
        InputData.hex = c.convertCharsToHex(InputData.chars);
        f.ofd.fileContents = InputData.chars;
    }

    ImGui::PopStyleVar();
    ImGui::PopStyleColor(3);
    ImGui::EndChild();
} 

void FileEditorView::FooterView(const ImVec2& pos, const float footerHeight, const float hexEditorWidth, const float charEditorWidth) {
    ImGui::SetCursorPos(pos);
    const float footerWidth = ImGui::GetWindowWidth();
    ImGui::BeginChild("Footer", ImVec2(footerWidth, footerHeight), ImGuiChildFlags_Borders);

    if(tc.showOffset) {
        std::size_t offset = InputData.chars.size();
        ImGui::Text(std::format("Offset: 0x{:X}", offset).c_str()); // https://www.modernescpp.com/index.php/std-format-in-c-20/
    }
    
    if(tc.showFPS) {
        ImGui::SameLine(footerWidth - 110.0f);
        ImGui::Text("%.1f FPS", ImGui::GetIO().Framerate);
    }

    ImGui::EndChild();
}