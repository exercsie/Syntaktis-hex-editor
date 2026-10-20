#pragma once

#include <expected>             // std::expected
#include <iostream>             // std::cout
#include <type_traits>          // std::is_void_v

namespace ErrorHandling {
    // Error handling
    template<typename T, typename Y>
    bool templateErrorHandling(const std::expected<T, Y>& result) {
        if(!result) {
            std::cout << result.error() << std::endl;
            return false;
        }
    
        if constexpr (!std::is_void_v<T>) {
            std::cout << *result << std::endl;
            return true;
        }
    
        return true;
    }
}