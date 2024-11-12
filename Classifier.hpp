#ifndef CLASSIFIER_HPP
#define CLASSIFIER_HPP

#include <fstream>

#include "Trie.hpp"
#include "IllegalArgument.hpp"

class Classifier
{
private:
    Trie *trie;

public:
    Classifier();
    ~Classifier();

    void validateInput(const string &input);
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