#pragma once

#include "Gui.hpp"
#include "ByteLogic.hpp"

class FileEditorView {
public:
    // Constructor / Destructor
    explicit FileEditorView();
    explicit FileEditorView(File& file) : f(file) {}
    ~FileEditorView() = default;

    // Views
    void FileMainView(ImVec2& displaySize);
    void hexEditorView(const ImVec2&, const float hexWidth, const float height);
    void charEditorView(const ImVec2&, const float firstX, const float width, const float height);

    struct DynamicInputData {
        std::string chars;
        std::string hex;
    };

    DynamicInputData InputData;
private:
    File& f;
    Conversion c;
};