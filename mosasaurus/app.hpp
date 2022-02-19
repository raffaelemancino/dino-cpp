#ifndef APP
#define APP

#include <iostream>
#include <map>
#include <string>

#include "ioc.hpp"

namespace Mosasaurus
{
    class App
    {
    private:
        IoC::Context *context = 0;

    public:
        App();
        ~App();
        App(const App &);
        void configure(std::map<std::string, IoC::Injectable *>);
        IoC::Context *getContext();
    };
}

#endif
