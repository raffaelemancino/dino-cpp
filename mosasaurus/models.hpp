#ifndef MODELS
#define MODELS

#include "mongoose-cpp/mongoose/WebController.h"
#include "mongoose-cpp/mongoose/JsonController.h"

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

        /**
         *  Function to be called for inject other services
         */
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

    class Controller : public Component, public Mongoose::WebController
    {
    };

    class RestController : public Component, public Mongoose::JsonController
    {
    };
}

#endif