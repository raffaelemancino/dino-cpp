#include <iostream>
#include <map>

#include "dino/dino.hpp"

#include "dino/recursion/ddfs.hpp"

using namespace std;

int main()
{
    Graph *n = new Graph();
    n->addElement("A", "B");
    n->addElement("A", "D");
    n->addElement("B", "D");
    n->addElement("D", "A");
    std::cout << n->isCyclic() << std::endl;
}