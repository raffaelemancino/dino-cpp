#pragma once

#include <string>
#include <vector>

class Node
{
private:
    std::string name;
    std::vector<std::string> adj;

public:
    bool visited = false;
    bool inPath = false;

    Node(std::string n)
    {
        this->name = n;
    }

    std::string getName()
    {
        return this->name;
    }

    void addNode(std::string n)
    {
        this->adj.push_back(n);
    }

    std::vector<std::string> getAdjencies()
    {
        return this->adj;
    }
};