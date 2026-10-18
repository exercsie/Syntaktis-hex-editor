#include "ByteLogic.hpp"
#include "../Dependencies/cppcodec/cppcodec/hex_upper.hpp"

#include <cctype>           // std::isxdigit, std::toupper
#include <cstdint>          // std::uint8_t
#include <string>           // std::string

std::string Conversion::convertHexToChar(const std::string& input) {
    std::string temp;
    for(std::uint8_t i : input) {
        if(std::isxdigit(i)) {
            temp.push_back(std::toupper(i));
        }
    }

    // remove trailing odd byte to make a hex char
    if(temp.size() & 1) {
        temp.pop_back();
    }

    return cppcodec::hex_upper::decode<std::string>(temp);
}

std::string Conversion::convertCharsToHex(const std::string& chars) {
    return cppcodec::hex_upper::encode(chars);
}