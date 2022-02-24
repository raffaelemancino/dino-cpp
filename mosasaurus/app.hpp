#ifndef APP
#define APP

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <cstring>
#include <thread>

#include "mongoose-cpp/mongoose/Server.h"

#include "module.hpp"

namespace Mosasaurus
{
    class MosaApp
    {
    private:
        static MosaApp *app;
        MosaModule *bootstrapModule = nullptr;
        MosaApp();
        void startupLogo();

        // web server
        Mongoose::Server *server = nullptr;

    public:
        static MosaApp *getInstance();

        template <class M>
        void bootstrap()
        {
            MosaModule *firstModule = new M();
            this->bootstrapModule = firstModule;
            std::cout << "App configuration End" << std::endl;
        };
        void bind(int, std::string);
    };
}

#endif
