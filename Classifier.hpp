#ifndef CLASSIFIER_HPP
#define CLASSIFIER_HPP

#include <fstream>

#include "Trie.hpp"
#include "illegal_exception.hpp"

class Classifier
{
private:
    Trie *trie;

    void validateInput(const string &input);

public:
    Classifier();
    ~Classifier();

    void load(const string &filename);
    string insert(const string &classification);
    string classify(const string &input);
    string erase(const string &classification);
    void print() const;
    bool empty() const;
    void clear();
    int size() const;
};

#endif