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
        void bootstrap(MosaModule *);
    };
}

#endif
