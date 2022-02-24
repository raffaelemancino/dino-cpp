#ifndef MODELS
#define MODELS

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

    class Controller : public Component
    {
    };
}

#endif