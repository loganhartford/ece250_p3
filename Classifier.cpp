#include "Classifier.hpp"

Classifier::Classifier()
{
    trie = new Trie();
}

Classifier::~Classifier()
{
    delete trie;
}

void Classifier::validateInput(const string &input)
{
    for (char ch : input)
    {
        if (isupper(static_cast<unsigned char>(ch)))
        {
            throw IllegalArgument();
        }
    }
}

void Classifier::load(const string &filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        // Delete this later
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line))
    {
        trie->insert(line);
    }

    file.close();
}

string Classifier::insert(const string &classification)
{
    try
    {
        validateInput(classification);
        if (trie->insert(classification))
        {
            return "success";
        }
        else
        {
            return "failure";
        }
    }
    catch (const IllegalArgument &e)
    {
        return e.what();
    }
}

string Classifier::classify(const string &input)
{
    try
    {
        validateInput(input);
        return trie->classify(input);
    }
    catch (const IllegalArgument &e)
    {
        return e.what();
    }
}

string Classifier::erase(const string &classification)
{
    try
    {
        validateInput(classification);
        if (trie->erase(classification))
        {
            return "success";
        }
        else
        {
            return "failure";
        }
    }
    catch (const IllegalArgument &e)
    {
        return e.what();
    }
}

void Classifier::print() const
{
    trie->print();
}

bool Classifier::empty() const
{
    return trie->getSize() == 0;
}

void Classifier::clear()
{
    trie->clear();
}

int Classifier::size() const
{
    return trie->getSize();
}