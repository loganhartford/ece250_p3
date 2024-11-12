#ifndef TRIENODE_HPP
#define TRIENODE_HPP

#include <string>
#include <vector>
using namespace std;

class TrieNode
{

private:
    static constexpr int MAX_CHILDREN = 15;
    vector<TrieNode *> children;

public:
    string label;
    bool isTerminal;

    TrieNode();
    ~TrieNode();

    bool isChild(string label);
    bool addChild(string label);
    bool removeChild(string label);
    bool hasChildren();
    TrieNode *getChild(string label);
    string getChildrenString();
    vector<TrieNode *> getChildren();
};

#endif