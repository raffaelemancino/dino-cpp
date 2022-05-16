/*
Copyright (C) 2022 Raffaele Francesco Mancino <raffaelefrancesco.mancino@gmail.com>

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Library General Public
License as published by the Free Software Foundation; either
version 2 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Library General Public License for more details.

You should have received a copy of the GNU Library General Public
License along with this library; if not, write to the
Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
Boston, MA  02110-1301, USA.
*/

#pragma once

#include <vector>
#include <string>
#include <iostream>

#include "node.hpp"

class Graph
{
private:
    std::vector<Node *> nodes;
    std::string cycleNodes;

    bool findNode(std::string name)
    {
        for (Node *node : this->nodes)
        {
            if (node->getName() == name)
            {
                return true;
            }
        }

        return false;
    }

    Node *getNode(std::string name)
    {
        for (Node *node : this->nodes)
        {
            if (node->getName() == name)
            {
                return node;
            }
        }

        return nullptr;
    }

    void resetInPath()
    {
        this->cycleNodes = "";
        for (Node *node : this->nodes)
        {
            node->inPath = false;
        }
    }

public:
    void addElement(std::string node, std::string nodeAdj)
    {
        if (!this->findNode(node))
        {
            this->nodes.push_back(new Node(node));
        }

        if (!this->findNode(nodeAdj))
        {
            this->nodes.push_back(new Node(nodeAdj));
        }

        this->getNode(node)->addNode(nodeAdj);
    }

    // public void DFS(string name)
    // {
    //     write(name ~ "; ");

    //     if (name !in this.nodes)
    //     {
    //         throw new Exception("Node " ~ name ~ " not found");
    //     }
    //     Node n = this.nodes[name];
    //     n.visited = true;

    //     foreach (string arc; n.getAdjencies())
    //     {
    //         Node arcNode = this.nodes[arc];
    //         if (!arcNode.visited)
    //         {
    //             this.DFS(arc);
    //         }
    //     }
    // }

    bool isCyclic(Node *n)
    {
        if (n->visited)
        {
            n->visited = true;
            n->inPath = true;
            for (std::string adjName : n->getAdjencies())
            {
                Node *adj = this->getNode(adjName);
                if (!adj->visited && this->isCyclic(adj))
                {
                    return true;
                }
                else if (adj->inPath)
                {
                    return true;
                }
            }
        }
        n->inPath = false;
        return false;
    }

    bool isCyclic()
    {
        this->resetInPath();
        for (Node *node : this->nodes)
        {
            if (!node->visited && this->isCyclic(node))
            {
                std::cout << this->cycleNodes << std::endl;
                return true;
            }
        }

        return false;
    }
};