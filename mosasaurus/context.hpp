#ifndef CONTEXT
#define CONTEXT

#include <iostream>
#include <string>
#include <map>

#include "models.hpp"

// forward declaration
namespace IoC
{
    class Injectable;
}

namespace Mosasaurus
{

    class MosaContext
    {
    private:
        std::map<std::string, IoC::Injectable *> injectionMap;

    public:
        template <class T>
        T *inject(std::string name)
        {
            IoC::Injectable *value = 0;
            value = this->injectionMap[name];
            if (!value)
            {
                throw std::invalid_argument("Injectable reference not foud");
            }

            return (T *)value;
        };
        void addMapContext(std::string, IoC::Injectable *);
    };

};

#endif
