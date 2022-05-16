#pragma once

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <cstring>
#include <thread>

#include "mongoose-cpp/mongoose/Server.h"

#include "module.hpp"
#include "utils.hpp"

namespace Dino {
    class Module;

    class App
    {
    private:
        static App *app;
        Module *bootstrapModule = nullptr;
        App();
        void startupLogo();

        void bootstrap(Module*);

        // web server
        Mongoose::Server *server = nullptr;

    public:
        static App *getInstance();

        Mongoose::Server *getServerInstance();

        /**
         * App start with first module
         */
        template <class M>
        void bootstrap()
        {
            Logger::getInstance()->log("Loading App service and controllers...");
            Module *firstModule = new M();
            this->bootstrap(firstModule);
        };

        /**
         *  Start Web Server with port and base url
         */
        void bind(int, std::string);
    };
}