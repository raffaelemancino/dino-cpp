#pragma once

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <cstring>
#include <thread>

#include "mongoose-cpp/mongoose/Server.h"

#include "models.hpp"

namespace Dino
{
    class Module
    {
    private:
        Module *parentModule = nullptr;
        std::string name = "";
        std::map<std::string, IoC::Injectable *> services;
        std::map<std::string, IoC::Controller *> controllers;
        std::map<std::string, Module *> imports;

        std::map<std::string, IoC::Injectable *> exportedServices;
        std::map<std::string, Module *> exportedModules;

        void registerController(IoC::Controller *);

        IoC::Injectable *inject(std::string);

    protected:
        Module();

        template <class T>
        void addService(std::string name)
        {
            if (std::is_base_of<IoC::Injectable, T>::value)
            {
                IoC::Injectable *service = new T();
                service->name = name;
                this->addService(service);
            }
            else
            {
                std::cout << "Service " << name << " is not Injectable" << std::endl;
            }
        }

        template <class T>
        void addController(std::string name)
        {
            if (std::is_base_of<IoC::Controller, T>::value)
            {
                IoC::Controller *controller = new T();
                controller->name = name;
                this->addController(controller);
            }
            else
            {
                std::cout << "Controller " << name << " is not Injectable" << std::endl;
            }
        }

        template <class T>
        void addModule(std::string name)
        {
            if (std::is_base_of<Module, T>::value)
            {
                Module *mosaModule = new T();
                mosaModule->name = name;
                this->addModule(mosaModule);
            }
            else
            {
                std::cout << name << " is not a Module" << std::endl;
            }
        }

        void addExportService(std::string name);
        void addExportModule(std::string name);

        void addController(IoC::Controller *);
        void addService(IoC::Injectable *);
        void addModule(Module *);

    public:
        /**
         * Inject service searching in self module and in child modules
         */
        template <class T>
        T *inject(std::string name)
        {
            return (T *)this->inject(name);
        };

        /**
         *  Serach if child module have a serice
         */
        IoC::Injectable *injectForModuleParent(std::string name);

        /**
         *  Search if parent module have a service
         */
        IoC::Injectable *injectForModuleChild(std::string);

        /**
         *  Set its partend module for service search
         */
        void setParentModule(Module *);

        /**
         *  Compulsory function to avoid IoC in module
         */
        void registerInjectables();
    };

    class MosaApp
    {
    private:
        static MosaApp *app;
        Module *bootstrapModule = nullptr;
        MosaApp();
        void startupLogo();

        // web server
        Mongoose::Server *server = nullptr;

    public:
        static MosaApp *getInstance();

        Mongoose::Server *getServerInstance();

        /**
         * App start with first module
         */
        template <class M>
        void bootstrap()
        {
            std::cout << "Loading App service and controllers..." << std::endl;
            Module *firstModule = new M();
            this->bootstrapModule = firstModule;
            this->bootstrapModule->registerInjectables();
            std::cout << "App configuration End" << std::endl;
        };
        /**
         *  Start Web Server with port and base url
         */
        void bind(int, std::string);
    };
}
