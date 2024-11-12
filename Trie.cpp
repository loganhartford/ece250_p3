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
    TrieNode *current = root;
    TrieNode *parent = nullptr;
    istringstream stream(classification);
    string label;

    while (getline(stream, label, ','))
    {
        if (!current->isChild(label))
        {
            return false;
        }
        parent = current;
        current = current->getChild(label);
    }

    if (!current->isTerminal)
    {
        return false;
    }
    parent->removeChild(label);

    if (parent->hasChildren())
    {
        parent->isTerminal = false;
    }
    else
    {
        parent->isTerminal = true;
    }
    return true;
}

string Trie::classify(const string &input)
{
    TrieNode *current = root;
    string classification = "";

    while (current->hasChildren())
    {
        string candidateLables = current->getChildrenString();
        string nextChild = labelText(input, candidateLables);
        if (current->isChild(nextChild))
        {
            current = current->getChild(nextChild);
            if (classification == "")
            {
                classification = nextChild;
            }
            else
            {
                classification += "," + nextChild;
            }
        }
        else
        {
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
    }
    cout << endl;
}

bool Trie::empty() const
{
    return !root->hasChildren();
}

void Trie::clear()
{
    delete root;
    root = new TrieNode();
}

int Trie::size() const
{
    vector<string> classifications;
    string currentClassification;

    printHelper(root, currentClassification, classifications);

    return classifications.size();
}
