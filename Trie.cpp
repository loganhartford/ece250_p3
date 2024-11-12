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

void Trie::setTerminal(TrieNode *node, bool terminal)
{
    // Update the size of the trie
    if (terminal and (terminal != node->isTerminal()))
    {
        size++;
    }
    else if (!terminal and (terminal != node->isTerminal()))
    {
        size--;
    }

    node->setTerminal(terminal);
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
        setTerminal(current, false);
        current = current->getChild(label);
    }

    // If the classification already exists, return false
    if (current->isTerminal())
    {
        return false;
    }
    setTerminal(current, true);
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

    if (!current->isTerminal())
    {
        return false;
    }
    parent->removeChild(label);

    if (parent->hasChildren())
    {
        setTerminal(parent, false);
    }
    else
    {
        setTerminal(parent, true);
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
    if (node->isTerminal())
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
            currentClassification += child->getLabel();

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

int Trie::getSize() const
{
    return size;
}
