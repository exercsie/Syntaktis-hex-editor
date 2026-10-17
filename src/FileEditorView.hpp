#pragma once

#include "Gui.hpp"

class FileEditorView {
public:
    // Constructor / Destructor
    explicit FileEditorView();
    explicit FileEditorView(File& file) : f(file) {}
    ~FileEditorView() = default;

    void FileMainView(ImVec2& displaySize);
    void hexEditorView(const ImVec2&, const float, const float);
    void charEditorView(const ImVec2&, const float, const float);
private:
    File& f;
};