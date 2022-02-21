#ifndef MODULE
#define MODULE

#include <map>
#include <vector>
#include <string>
#include <iostream>

#include "models.hpp"

namespace Mosasaurus
{
    class MosaModule

    {
    private:
        std::map<std::string, IoC::Injectable *> services;
        std::map<std::string, IoC::Controller *> controllers;
        std::map<std::string, MosaModule *> imports;

        Mosasaurus::MosaContext *context = 0;

    protected:
        MosaModule();
        void registerInjectables();

        template <class T>
        void addService(std::string name)
        {
            if (std::is_base_of<IoC::Injectable, T>::value)
            {
                IoC::Injectable *service = new T();
                this->services.insert(std::make_pair(name, service));
                this->context->addMapContext(name, service);
                std::cout << "Adding service: " << name << std::endl;
                service->setContext(this->context);
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
                this->controllers.insert(std::make_pair(name, controller));
                std::cout << "Adding controller: " << name << std::endl;
                controller->setContext(this->context);
            }
            else
            {
                std::cout << "Controller " << name << " is not Injectable" << std::endl;
            }
        }

        template <class T>
        void addModule(std::string name)
        {
            if (std::is_base_of<MosaModule, T>::value)
            {
                MosaModule *mosaModule = new T();
                this->imports.insert(std::make_pair(name, mosaModule));
                std::cout << "Adding module: " << name << std::endl;
            }
            else
            {
                std::cout << name << " is not a Module" << std::endl;
            }
        }
    };

};

#endif