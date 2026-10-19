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
    std::string hex = cppcodec::hex_upper::encode(chars);
    std::string output;

    for(std::size_t i{}; i < hex.size(); i += 2) {
        // Add space after every hexadecimal val
        if(i > 0) {
            output += ' ';
        }

        // app the next two hexa-decimal vals onto output
        output += hex.substr(i, 2);
    }

    return output;
}