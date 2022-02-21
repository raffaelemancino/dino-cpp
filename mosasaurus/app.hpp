#ifndef APP
#define APP

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "module.hpp"

namespace Mosasaurus
{
    class MosaApp
    {
    private:
        static MosaApp *app;
        MosaModule *bootstrapModule;
        MosaApp();
        void startupLogo();

    public:
        static MosaApp *getInstance();

        template <class M>
        void bootstrap()
        {
            MosaModule *firstModule = new M();
            this->bootstrapModule = firstModule;
            std::cout << "App configuration End" << std::endl;
        };
    };
}

#endif
