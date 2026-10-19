#pragma once

#include <string>           // std::string

class Conversion {
public:
    // Constructor / Destructor
    explicit Conversion() = default;
    ~Conversion() = default;

    // Conversion Logic
    static std::string convertHexToChar(const std::string&);
    static std::string convertCharsToHex(const std::string&);
};