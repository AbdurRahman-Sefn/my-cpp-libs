#pragma once

#include <iostream>
#include <sstream>

template<typename T>
T read_validated_input(const std::string& prompt, int indent_tabs = 0,
                       bool (*validator)(T) = nullptr, 
                       const std::string& error_message = "Invalid value. Please try again.\n") {
    T value;
    std::string line;
    std::string indent = indenter(indent_tabs);
    std::cout << indent << prompt;
    indent.push_back('\t');
    while (true) {
        std::getline(std::cin, line);
        std::stringstream ss(line);

        if ((ss >> value) && (ss.eof())) {
            //if there is a validation function, then use it
            if (validator == nullptr || validator(value)) {
                break; // input is valid
            } else {
                std::cout << indent << error_message;
            }
        } else {
            std::cout << indent << "Invalid format. Please try again.\n";
        }
    }
    return value;
}