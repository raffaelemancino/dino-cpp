#ifndef CONTEXT
#define CONTEXT

#include <iostream>
#include <string>
#include <map>
#include <microhttpd.h>

namespace IoC
{
    class Injectable
    {
    };

    class Bean : public Injectable
    {
    };

    class Component : public Bean
    {
    };

    class Service : public Component
    {
    };

    class Controller : public Component
    {
    public:
        Controller();
    };

    class Context
    {
    private:
        static Context *context;
        std::map<std::string, Injectable *> injectionMap;
        Context();

    public:
        static Context *getInstance();
        Injectable *inject(std::string);
        void addMapContext(std::string, Injectable *);
    };
};

#endif
