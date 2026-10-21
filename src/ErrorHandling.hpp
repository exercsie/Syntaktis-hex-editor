#pragma once

#include "../Dependencies/imgui/imgui.h"
#include "Gui.hpp"

#include <expected>             // std::expected
#include <iostream>             // std::cout
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
            lg.logs.push_back({ result.error(), true });
            return false;
        }
    
        if constexpr (!std::is_void_v<T>) {
            lg.logs.push_back({ *result, false });
        }
    
        return true;
    }
}