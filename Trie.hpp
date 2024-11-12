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

public:
    Trie();
    ~Trie();

    void setTerminal(TrieNode *node, bool terminal);
    bool insert(const string &classification);
    bool erase(const string &classification);
    string classify(const string &input);
    void printHelper(TrieNode *node, string &currentClassification, vector<string> &classifications) const;
    void print() const;
    bool empty() const;
    void clear();
    int getSize() const;
};

#endif