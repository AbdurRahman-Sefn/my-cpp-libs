# My C++ Header-Only Libraries

## Overview

Welcome! This repository is a showcase of my C++ skills, presented as a collection of reusable, header-only utility libraries. The code is written using modern C++ practices and is designed to be both efficient and easy to integrate into other projects.

## Libraries

This collection currently includes:

1.  **Trie (`Dictionary.hpp`):** A powerful prefix tree for string-related operations.
2.  **Validated Input (`input_utils.hpp`):** A safe and flexible utility for reading user console input.

---

### 1. Trie (`Dictionary.hpp`)

This header provides a generic and efficient implementation of a **Trie** (also known as a Prefix Tree). It is named `Dictionary` in the code. This data structure is particularly well-suited for tasks that involve prefix-based searching, like auto-completion engines or spell checkers.

#### Features

-   **Generic:** Can store pointers to any object type (`template<class T>`).
-   **Efficient Lookups:** Fast insertion and search operations for words and prefixes.
-   **Auto-completion:** Built-in function to find all words/objects associated with a given prefix.
-   **Modern C++:** Uses features like smart resource management (RAII) and deleted copy semantics for safety.
-   **Ownership Model:** The Trie does **not** take ownership of the stored pointers. You are responsible for managing the memory of the objects you insert.

#### Example Usage

```cpp
#include <iostream>
#include <string>
#include <vector>
#include "Dictionary.hpp"

int main() {
    Dictionary<std::string> trie;

    // Associate std::string objects with words
    auto apple = std::string("An apple a day...");
    auto apply = std::string("To apply for the job...");
    auto banana = std::string("A yellow fruit.");

    trie.insert(&apple, "apple");
    trie.insert(&apply, "apply");
    trie.insert(&banana, "banana");

    // Use auto-complete to find all words starting with "app"
    std::vector<std::string*> results;
    trie.auto_complete("app", results);

    std::cout << "Words starting with 'app':" << std::endl;
    for (const auto* str_ptr : results) {
        std::cout << "- " << *str_ptr << std::endl;
    }
    // Note: Memory for apple, apply, banana must be managed manually.

    return 0;
}
```

---

### 2. Validated Input (`input_utils.hpp`)

This header provides a simple yet powerful template function, `read_validated_input`, for reading and validating user input from the console. It helps prevent common input errors and ensures that the data conforms to your specified rules.

#### Features

-   **Type-Safe:** Reads and parses input directly into the desired C++ type (`int`, `double`, `std::string`, etc.).
-   **Flexible Validation:** Accepts any callable (function pointer, functor, or lambda) to validate the input.
-   **User-Friendly:** Automatically re-prompts the user with a custom error message on invalid input.

#### Example Usage

```cpp
#include <iostream>
#include "input_utils.hpp"

int main() {
    // Read an integer between 18 and 65
    int age = read_validated_input<int>(
        "Please enter your age (18-65): ",
        0, // No indentation
        [](const int& val) {
            return val >= 18 && val <= 65;
        },
        "Invalid age. Please try again.\n"
    );

    std::cout << "Thank you. Your age is: " << age << std::endl;

    return 0;
}
```

---

## How to Use

These are header-only libraries, which makes them very easy to use:

1.  Clone this repository or download the files.
2.  Copy the header files from this directory into your project's include path.
3.  `#include` the desired header file in your code.

Example:
```cpp
#include "path/to/your/includes/Dictionary.hpp"
#include "path/to/your/includes/input_utils.hpp"
```
