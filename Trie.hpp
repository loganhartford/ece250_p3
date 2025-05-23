#ifndef TRIE_HPP
#define TRIE_HPP

#include <iostream>
#include <sstream>

#include "TrieNode.hpp"

class Trie
{
private:
    TrieNode *root;
    int size;

    void printHelper(TrieNode *node, string &currentClassification, vector<string> &classifications) const;
    void setTerminal(TrieNode *node, bool terminal);

public:
    Trie();
    ~Trie();

    bool insert(const string &classification);
    bool erase(const string &classification);
    string classify(const string &input);
    string print() const;
    void clear();
    int getSize() const;
};

#endif