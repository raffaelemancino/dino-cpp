#include "context.hpp"

using namespace Mosasaurus;

void MosaContext::addMapContext(std::string name, IoC::Injectable *injectable)
{
    this->injectionMap.insert(std::make_pair(name, injectable));
}