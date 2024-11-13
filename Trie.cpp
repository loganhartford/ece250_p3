#include "ece250_socket.hpp"

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
    if (node == root)
    {
        return;
    }
    // Update the size of the trie
    if (terminal and (terminal != node->isTerminal()))
    {
        size++;
    }
    else if (!terminal and (terminal != node->isTerminal()))
    {
        size--;
    }

    // Calling the nodes methods, not a recursive call
    node->setTerminal(terminal);
}

bool Trie::insert(const string &classification)
{
    TrieNode *current = root;
    TrieNode *addedChild = nullptr;
    istringstream stream(classification);
    string label;

    // Traverse the trie and create new nodes if necessary
    while (getline(stream, label, ','))
    {
        if (!current->isChild(label))
        {
            if (!current->addChild(label))
            {
                return false;
            }
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
    vector<TrieNode *> path; // To keep track of the nodes along the path
    istringstream stream(classification);
    string label;

    // Traverse the trie and record the path
    while (getline(stream, label, ','))
    {
        if (!current->isChild(label))
        {
            return false; // Classification not found
        }
        current = current->getChild(label);
        path.push_back(current);
    }

    if (!current->isTerminal())
    {
        return false; // Classification not found
    }

    setTerminal(current, false); // Unmark the terminal node

    // Clean up unnecessary nodes
    for (int i = path.size() - 1; i >= 0; --i)
    {
        TrieNode *node = path[i];
        TrieNode *parent = (i > 0) ? path[i - 1] : root;

        if (!node->hasChildren() && !node->isTerminal())
        {
            parent->removeChild(node);
            delete node;
        }
        else
        {
            break; // Stop if the node is needed
        }
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

string Trie::print() const
{
    if (!root->hasChildren())
    {
        return "trie is empty";
    }

    vector<string> classifications;
    string currentClassification;
    string returnString = "";

    printHelper(root, currentClassification, classifications);

    for (size_t i = 0; i < classifications.size(); ++i)
    {
        returnString += classifications[i] + "_";
    }
    return returnString;
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
