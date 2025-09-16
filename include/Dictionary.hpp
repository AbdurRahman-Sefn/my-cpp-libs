#pragma once
#include <map>
#include <iostream>
#include <vector>


template<class T>
class Dictionary{
    T* object = nullptr;
    std::map<char, Dictionary*> childs;
    const Dictionary* find(const std::string &prefix) const{
        const Dictionary* cur = this;
        for(char c : prefix){
            auto it = cur->childs.find(c); 
            if(it == cur->childs.cend()){
                return nullptr;
            }
            cur = it->second;
        }
        return cur;
    }
    Dictionary* find(const std::string &prefix){
        return const_cast<Dictionary*>(static_cast<const Dictionary*> (this)->find(prefix));
    }
    void get_all_objects(std::vector<T*> &res)const{
        this->traverse_recursive([&res](T* object){
            res.push_back(object);
        });
    }
    template<typename Func>
    void traverse_recursive(Func func) const {
        if (object) {
            func(object);
        }
        for (auto const& [c, child] : childs) {
            child->traverse_recursive(func);
        }
    }
public:
    Dictionary(const Dictionary &) = delete;
    Dictionary &operator=(const Dictionary&) = delete;
    Dictionary() = default;
    void insert(T *object,const std::string &word){
        Dictionary* cur = this;
        for(int i = 0; i < word.size(); ++i){
            Dictionary* &child = cur->childs[word[i]];
            if(!child){
                child = new Dictionary;
            }
            cur = child;
        }
        cur->object = object;
    }
    T* word_exist(const std::string &word){
            return const_cast<T*>(static_cast<const Dictionary*>(this)->word_exist(word));
    }
    const T* word_exist(const std::string &word)const{
        const Dictionary *cur = find(word);
        return cur && cur->object ? cur->object : nullptr;
    }
    bool prefix_exist(const std::string &prefix)const{
        const Dictionary* res = find(prefix);
        return res != nullptr;
    }
    template<typename Func>
    void traverse(Func func) const {
        this->traverse_recursive(func);
    }
    void auto_complete(const std::string &prefix, std::vector<T*> &res)const{
        const Dictionary* root = find(prefix);
        if(root){
            root->get_all_objects(res);
        }
    }
    void clear(){
        for(auto &[c, child] : childs){
            delete child;
            child = nullptr;
        }
        childs.clear();
    }
    ~Dictionary(){
        clear();
    }
};