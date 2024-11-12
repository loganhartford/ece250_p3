#include "ece250_socket.h"

#include "Trie.hpp"

Trie::Trie()
{
    root = new TrieNode();
}

Trie::~Trie()
{
    delete root;
}

bool Trie::insert(const string &classification)
{
    TrieNode *current = root;
    istringstream stream(classification);
    string label;

    // Traverse the trie and create new nodes if necessary
    while (getline(stream, label, ','))
    {
        if (!current->isChild(label))
        {
            current->addChild(label);
        }
        // Internal nodes can't be terminal
        current->isTerminal = false;
        current = current->getChild(label);
    }

    // If the classification already exists, return false
    if (current->isTerminal)
    {
        return false;
    }
    current->isTerminal = true;
    return true;
}

bool Trie::erase(const string &classification)
{
    vector<TrieNode *> path;
    TrieNode *current = root;
    istringstream stream(classification);
    string label;

    // Traverse the trie and track the traversed path
    while (getline(stream, label, ','))
    {
        if (!current->isChild(label))
        {
            return false;
        }
        path.push_back(current);
        current = current->getChild(label);
    }

    // If the classification does not exist, return false
    if (!current->isTerminal)
    {
        return false;
    }
    current->isTerminal = false;

    // Remove nodes that are no longer needed
    for (int i = path.size() - 1; i >= 0; --i)
    {
        TrieNode *parent = path[i];
        if (!current->hasChildren() && !current->isTerminal)
        {
            parent->removeChild(label);
        }
        current = parent;
    }
    return true;
}

string Trie::classify(const string &input)
{
    TrieNode *current = root;
    string classification;

    while (current->hasChildren())
    {
        string candidateLables = current->getChildrenString();
        string nextChild = labelText(input, candidateLables);
        if (current->isChild(nextChild))
        {
            current = current->getChild(nextChild);
            classification += nextChild + ",";
        }
        else
        {
            classification += nextChild;
            break;
        }
    }

    return classification;
}

void Trie::printHelper(TrieNode *node, string &currentClassification, vector<string> &classifications) const
{
    if (node->isTerminal)
    {
        classifications.push_back(currentClassification);
    }

    for (TrieNode *child : node->getChildren())
    {
        if (child != nullptr)
        {
            string previousClassification = currentClassification;
            if (!currentClassification.empty())
            {
                currentClassification += ",";
            }
            currentClassification += child->label;

            printHelper(child, currentClassification, classifications);

            currentClassification = previousClassification; // Backtrack
        }
    }
}

void Trie::print() const
{
    if (!root->hasChildren())
    {
        cout << "trie is empty" << endl;
        return;
    }

    vector<string> classifications;
    string currentClassification;

    printHelper(root, currentClassification, classifications);

    for (size_t i = 0; i < classifications.size(); ++i)
    {
        cout << classifications[i] << "_";
        ;
        // if (i != classifications.size() - 1)
        // {
        //     cout << "_";
        // }
    }
    cout << endl;
}
