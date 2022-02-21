#ifndef MODELS
#define MODELS

#include "context.hpp"

// forward declaration
namespace Mosasaurus
{
    class MosaContext;
};

namespace IoC
{
    class Injectable
    {
    protected:
        Mosasaurus::MosaContext *context = 0;

    public:
        void setContext(Mosasaurus::MosaContext *c);
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