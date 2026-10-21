#pragma once

#include <string>           // std::string

// Data
struct DynamicInputData {
    std::string chars;
    std::string hex;
};

struct ToggleCheckboxes {
    bool showLogs = false;
    bool showFPS = false;
    bool showOffset = true;
};