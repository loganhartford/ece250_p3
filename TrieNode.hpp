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
    int numChildren = 0;
    string label = "";
    bool terminalStatus = false;

public:
    TrieNode();
    ~TrieNode();

    bool isTerminal() const;
    void setTerminal(bool terminal);
    bool isChild(string label) const;
    bool addChild(string label);
    bool removeChild(TrieNode *child);
    bool hasChildren() const;
    TrieNode *getChild(string label) const;
    string getChildrenString() const;
    vector<TrieNode *> getChildren() const;
    string getLabel() const;
};

#endif