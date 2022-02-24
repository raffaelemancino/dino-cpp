#ifndef MODELS
#define MODELS

#include "context.hpp"

// forward declaration
namespace Mosasaurus
{
    class MosaModule;
};

namespace IoC
{
    class Injectable
    {
    protected:
        Mosasaurus::MosaModule *context = nullptr;

    public:
        void setContext(Mosasaurus::MosaModule *c);
        virtual void onLoadEnd(){};
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
    };
}

#endif