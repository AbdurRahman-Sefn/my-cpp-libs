#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <functional>

/**
 * @file input_utils.hpp
 * @brief A utility for reading and validating user input from the console.
 */

/**
 * @brief Reads and validates user input from the console.
 *
 * This function prompts the user for input, reads a line from the console,
 * and attempts to parse it into the specified type `T`. It can optionally
 * validate the parsed value using a provided validator function.
 *
 * @tparam T The data type of the value to be read.
 * @param prompt The message to display to the user.
 * @param indent_tabs The number of tabs to indent the prompt and messages.
 * @param validator A callable (function, lambda, etc.) that takes a value of type T
 *                  and returns true if the value is valid, false otherwise.
 *                  If nullptr, no validation is performed.
 * @param error_message The error message to display for invalid values.
 * @return The validated value of type T.
 */
template<typename T>
T read_validated_input(const std::string& prompt, int indent_tabs = 0,
                       const std::function<bool(const T&)>& validator = nullptr,
                       const std::string& error_message = "Invalid value. Please try again.\n") {
    T value;
    std::string line;
    std::string indent(indent_tabs, '\t');
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