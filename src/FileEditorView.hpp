#pragma once

#include "../Dependencies/imgui/imgui.h"
#include "DynamicInputData.hpp"
#include "ByteLogic.hpp"

class File;

class FileEditorView {
public:
    // Constructor / Destructor
    explicit FileEditorView(File& file, DynamicInputData& DynamicInputData, ToggleCheckboxes& checkboxes) : f(file), InputData(DynamicInputData), tc(checkboxes) {}
    ~FileEditorView() = default;

    // Views
    void FileMainView(ImVec2& displaySize);
    void hexEditorView(const ImVec2&, const float hexWidth, const float height);
    void charEditorView(const ImVec2&, const float firstX, const float width, const float height);
    void FooterView(const ImVec2&, const float, const float, const float);
private:
    File& f;
    ToggleCheckboxes& tc;
    DynamicInputData& InputData;
    Conversion c;
};