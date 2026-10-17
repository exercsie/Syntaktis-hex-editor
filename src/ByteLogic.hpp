#pragma once

#include <string>           // std::string

class Conversion {
public:
    Conversion() = default;
    ~Conversion() = default;

    static std::string convertHexToChar(const std::string&);
    static std::string convertCharsToHex(const std::string&);
};