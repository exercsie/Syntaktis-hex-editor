#pragma once

#include "../Dependencies/imgui/imgui.h"
#include "Gui.hpp"

#include <expected>             // std::expected
#include <format>               // std::format
#include <type_traits>          // std::is_void_v
#include <vector>               // std::vector

namespace ErrorHandling {
    struct LogEntry {
        std::string msg;
        bool isError;
    };

    // holds all logs
    struct Logs {
        std::vector<LogEntry> logs;
    };

   inline Logs lg;

    // Error handling
    template<typename T, typename Y>
    bool templateErrorHandling(const std::expected<T, Y>& result) {
        if(!result) {
            std::string errorMessage = std::format("[ERROR]: {}", result.error());
            lg.logs.push_back({ errorMessage, true });
            return false;
        }
    
        if constexpr (!std::is_void_v<T>) {
            std::string successMessage = std::format("[SUCCESS]: {}", *result);
            lg.logs.push_back({ successMessage, false });
        }
    
        return true;
    }
}