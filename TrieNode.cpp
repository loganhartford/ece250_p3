#include "TrieNode.hpp"

TrieNode::TrieNode()
{
    label = "";
    isTerminal = false;
    children.resize(MAX_CHILDREN, nullptr);
}

TrieNode::~TrieNode()
{
    for (TrieNode *child : children)
    {
        delete child;
    }
}

bool TrieNode::isChild(string label)
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

    for (int i = 0; i < children.size(); i++)
    {
        if (children[i] == nullptr)
        {
            children[i] = new TrieNode();
            children[i]->label = label;
            return true;
        }
    }
    return false;
}

bool TrieNode::removeChild(string label)
{
    for (int i = 0; i < children.size(); i++)
    {
        if (children[i] != nullptr && children[i]->label == label)
        {
            delete children[i];
            children[i] = nullptr;
            return true;
        }
    }
    return false;
}

bool TrieNode::hasChildren()
{
    for (TrieNode *child : children)
    {
        if (child != nullptr)
        {
            return true;
        }
    }
    return false;
}

TrieNode *TrieNode::getChild(string label)
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

string TrieNode::getChildrenString()
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

vector<TrieNode *> TrieNode::getChildren()
{
    return children;
}