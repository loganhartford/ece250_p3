#include "TrieNode.hpp"

TrieNode::TrieNode()
{
    label = "";
    terminal = false;
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
        if (child != nullptr && child->getLabel() == label)
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

vector<TrieNode *> TrieNode::getChildren()
{
    return children;
}