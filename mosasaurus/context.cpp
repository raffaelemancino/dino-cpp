#include "context.hpp"

using namespace Mosasaurus;

void MosaContext::addMapContext(std::string name, IoC::Injectable *injectable)
{
    this->injectionMap.insert(std::make_pair(name, injectable));
}

IoC::Injectable *MosaContext::inject(std::string name)
{
    IoC::Injectable *value = 0;
    value = this->injectionMap[name];
    if (!value)
    {
        throw std::invalid_argument("Injectable reference not foud");
    }

    return value;
}