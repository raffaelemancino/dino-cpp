#include "ioc.hpp"

using namespace IoC;

Context *Context::context = 0;

Context::Context()
{
}

Context *Context::getInstance()
{
    if (!context)
    {
        std::cout << "Init Execution Context" << std::endl;
        context = new Context();
    }

    return context;
}

void Context::addMapContext(std::string name, Injectable *injectable)
{
    this->injectionMap.insert(std::make_pair(name, injectable));
}

Injectable *Context::inject(std::string name)
{
    Injectable *value = 0;
    value = this->injectionMap[name];
    if (!value)
    {
        throw std::invalid_argument("Injectable reference not foud");
    }

    return value;
}