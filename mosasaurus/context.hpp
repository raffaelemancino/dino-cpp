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
        IoC::Injectable *inject(std::string);
        void addMapContext(std::string, IoC::Injectable *);
    };

};

#endif
