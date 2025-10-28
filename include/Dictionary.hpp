#pragma once

#include <map>
#include <iostream>
#include <vector>
#include <string>
#include <functional> // For std::function in traverse

/**
 * @file Dictionary.hpp
 * @brief Contains the implementation of a Trie (Prefix Tree) data structure.
 * @note While named Dictionary, this class is implemented as a Trie, making it
 *       highly efficient for prefix-based operations like auto-complete.
 */

template<class T>
class Dictionary {
private:
    /**
     * @brief Pointer to the object associated with a complete word.
     * @details This is nullptr if the node does not represent the end of a word.
     * @warning The Dictionary class does NOT take ownership of this pointer.
     *          Memory management of the object is the responsibility of the user.
     */
    T* object = nullptr;

    /**
     * @brief Map of child nodes, keyed by character.
     */
    std::map<char, Dictionary*> childs;

    /**
     * @brief Finds the node corresponding to the given prefix (const version).
     * @param prefix The prefix to search for.
     * @return A const pointer to the node if found, otherwise nullptr.
     */
    const Dictionary* find(const std::string &prefix) const {
        const Dictionary* cur = this;
        for (char c : prefix) {
            auto it = cur->childs.find(c);
            if (it == cur->childs.cend()) {
                return nullptr;
            }
            cur = it->second;
        }
        return cur;
    }

    /**
     * @brief Finds the node corresponding to the given prefix (non-const version).
     * @param prefix The prefix to search for.
     * @return A pointer to the node if found, otherwise nullptr.
     */
    Dictionary* find(const std::string &prefix) {
        return const_cast<Dictionary*>(static_cast<const Dictionary*>(this)->find(prefix));
    }

    /**
     * @brief Recursively gathers all objects in this subtree.
     * @param res A vector to store the pointers to the found objects.
     */
    void get_all_objects(std::vector<T*> &res) const {
        this->traverse_recursive([&res](T* obj) {
            res.push_back(obj);
        });
    }

    /**
     * @brief Recursively traverses the subtree and applies a function to each object.
     * @tparam Func The type of the callable function.
     * @param func The function to apply to each object pointer.
     */
    template<typename Func>
    void traverse_recursive(Func func) const {
        if (object) {
            func(object);
        }
        for (auto const& [key, child] : childs) {
            child->traverse_recursive(func);
        }
    }

public:
    /**
     * @brief Default constructor.
     */
    Dictionary() = default;

    /**
     * @brief Copy constructor is deleted to prevent shallow copies and double frees.
     */
    Dictionary(const Dictionary &) = delete;

    /**
     * @brief Copy assignment operator is deleted to prevent shallow copies.
     */
    Dictionary &operator=(const Dictionary&) = delete;

    /**
     * @brief Destructor. Frees the memory allocated for child nodes.
     * @note This does NOT deallocate the `T* object` pointers.
     */
    ~Dictionary() {
        clear();
    }

    /**
     * @brief Inserts a word into the dictionary and associates an object with it.
     * @param object A pointer to the object to associate with the word. The Dictionary
     *               does not take ownership of this pointer.
     * @param word The word to insert.
     * @note If the word already exists, its associated object pointer will be overwritten.
     */
    void insert(T *object, const std::string &word) {
        Dictionary* cur = this;
        for (char c : word) {
            Dictionary* &child = cur->childs[c];
            if (!child) {
                child = new Dictionary;
            }
            cur = child;
        }
        cur->object = object;
    }

    /**
     * @brief Checks if a word exists and returns a pointer to its associated object.
     * @param word The word to search for.
     * @return A pointer to the associated object if the word exists, otherwise nullptr.
     */
    T* word_exist(const std::string &word) {
        return const_cast<T*>(static_cast<const Dictionary*>(this)->word_exist(word));
    }

    /**
     * @brief Checks if a word exists (const version).
     * @param word The word to search for.
     * @return A const pointer to the associated object if the word exists, otherwise nullptr.
     */
    const T* word_exist(const std::string &word) const {
        const Dictionary *cur = find(word);
        return cur && cur->object ? cur->object : nullptr;
    }

    /**
     * @brief Checks if any word with the given prefix exists.
     * @param prefix The prefix to check.
     * @return True if the prefix exists, false otherwise.
     */
    bool prefix_exist(const std::string &prefix) const {
        return find(prefix) != nullptr;
    }

    /**
     * @brief Traverses the entire dictionary and applies a function to each object.
     * @tparam Func The type of the callable function (e.g., a lambda).
     * @param func The function to apply. It will be called with a `T*` for each object.
     */
    template<typename Func>
    void traverse(Func func) const {
        this->traverse_recursive(func);
    }

    /**
     * @brief Finds all words with a given prefix (auto-completion).
     * @param prefix The prefix to search for.
     * @param res A vector to which the pointers of matching objects will be added.
     */
    void auto_complete(const std::string &prefix, std::vector<T*> &res) const {
        const Dictionary* root = find(prefix);
        if (root) {
            root->get_all_objects(res);
        }
    }

    /**
     * @brief Clears the dictionary, deallocating all nodes.
     * @note This does NOT deallocate the `T* object` pointers themselves.
     */
    void clear() {
        for (auto &[c, child] : childs) {
            delete child;
            child = nullptr;
        }
        childs.clear();
    }
};
