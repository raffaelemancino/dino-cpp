#pragma once

#include "mongoose-cpp/mongoose/WebController.h"
#include "mongoose-cpp/mongoose/JsonController.h"

namespace Dino
{
    class Module;
}

namespace IoC
{
    class Injectable
    {
    protected:
        Dino::Module *context = nullptr;

    public:
        std::string name = "";
        void setContext(Dino::Module *c);

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

    class Controller : public Component, public Mongoose::Controller
    {
    public:
        virtual void registerApi(){};
    };

    class WebController : public Controller
    {
    };

    class RestController : public Controller
    {
    };
}