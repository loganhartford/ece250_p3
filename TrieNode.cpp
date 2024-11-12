#include "TrieNode.hpp"

TrieNode::TrieNode()
{
    children.resize(MAX_CHILDREN, nullptr);
}

TrieNode::~TrieNode()
{
    for (TrieNode *child : children)
    {
        if (child != nullptr)
        {
            delete child;
        }
    }
}

bool TrieNode::isTerminal() const
{
    return terminalStatus;
}

void TrieNode::setTerminal(bool terminal)
{
    terminalStatus = terminal;
}

bool TrieNode::isChild(string label) const
{
    for (TrieNode *child : children)
    {
        if (child != nullptr && child->label == label)
        {
            return true;
        }
    }
    return false;
}

bool TrieNode::addChild(string label)
{
    if (isChild(label))
    {
        return false;
    }

    if (numChildren + 1 > MAX_CHILDREN)
    {
        return false;
    }

    if (children[numChildren] == nullptr)
    {
        children[numChildren] = new TrieNode();
        children[numChildren]->label = label;
        numChildren++;
        return true;
    }
    return false;
}

bool TrieNode::removeChild(TrieNode *child)
{
    if (child == nullptr)
    {
        return false;
    }
    for (TrieNode *&node : children)
    {
        if (node == child)
        {
            delete node;
            node = nullptr;
            numChildren--;
            return true;
        }
    }
    return false;
}

bool TrieNode::hasChildren() const
{
    return numChildren > 0;
}

TrieNode *TrieNode::getChild(string label) const
{
    for (TrieNode *child : children)
    {
        if (child != nullptr && child->label == label)
        {
            return child;
        }
    }
    return nullptr;
}

string TrieNode::getChildrenString() const
{
    string childrenList = "";
    for (TrieNode *child : children)
    {
        if (child != nullptr)
        {
            if (childrenList == "")
            {
                childrenList += child->label;
            }
            else
            {
                childrenList += "," + child->label;
            }
        }
    }
    return childrenList;
}

vector<TrieNode *> TrieNode::getChildren() const
{
    return children;
}

string TrieNode::getLabel() const
{
    return label;
}